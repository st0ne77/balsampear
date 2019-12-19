#include "AVPlayer.h"
#include "AudioRenderer.h"
#include <iostream>
#include <map>

namespace balsampear
{
	AudioRenderer arender;
	AVPlayer::AVPlayer()
		:loaded(false),
		demuxerThread_("demux thread"),
		aDecoderThread_("audio decode thread"),
		vDecoderThread_("video decode thread"),
		videoRenderThread_("video render thread"),
		audioRenderThread_("audio render thread"),
		state_(PlayStatus::Status_end),
		clockmastertype_(ClockMasterType::AudioMaster),
		clockmaster_msec_(0)
	{
		arender.init();
		standardTimer.start(20, std::bind(&AVPlayer::calcTime, this));
	}

	AVPlayer::~AVPlayer()
	{
		standardTimer.exit();
		stop();
	}

	bool AVPlayer::load()
	{
		if (loaded)
			unload();
		parser_ = std::make_unique<AVParser>(file_);
		if (!parser_->parse())
			return false;

		demuxer_ = std::make_unique<AVDemuxer>();
		demuxer_->setFormatContext(parser_->getFormatCtx());

		int mediaType = parser_->getMediaType();
		if (mediaType & 0x1)
		{
			adecoder_ = AudioDecoder::create();
			if (adecoder_)
				adecoder_->setCodecContext(parser_->getAudioCodecCtx());
		}
		if (mediaType & 0x2)
		{
			vdecoder_ = VideoDecoder::create();
			if (vdecoder_)
				vdecoder_->setCodecContext(parser_->getVideoCodexCtx());
		}
		loaded = true;
		return loaded;
	}

	bool AVPlayer::load(const StringPiece& file)
	{
		if (state_ == PlayStatus::Status_playing)
		{
			stop();
		}
		setFile(file);
		return load();
	}

	void AVPlayer::unload()
	{
		parser_ = nullptr;
		demuxer_ = nullptr;
		adecoder_ = nullptr;
		vdecoder_ = nullptr;
		loaded = false;
	}

	void AVPlayer::setFile(const StringPiece& file)
	{
		file_ = file;
	}

	void AVPlayer::start()
	{
		if (loaded)
		{
			state_ = PlayStatus::Status_playing;
			startAllTask();
		}
	}

	void AVPlayer::seek(double pos)
	{
		state_ = PlayStatus::Status_end;
		arender.stop();
		stopAllTask();
		clearAll();
		double timestamp = parser_->duration() * pos;
		demuxer_->seek(timestamp);
		adecoder_->setSampleCount(timestamp * parser_->getAudioFormat().sampleRate());
		startAllTask();
		state_ = PlayStatus::Status_playing;
	}

	void AVPlayer::pause()
	{
		if (state_ == PlayStatus::Status_playing)
		{
			stopAllTask();
			state_ = PlayStatus::Status_pause;
		}
	}


	void AVPlayer::stop()
	{
		arender.stop();
		stopAllTask();
		state_ = PlayStatus::Status_end;
		clearAll();
		wakeAllThread();
		shared_ptr<VideoFrame> empty;
		clockmaster_msec_ = 0;
	}

	balsampear::AVPlayer::PlayStatus AVPlayer::status()
	{
		return state_;
	}


	bool AVPlayer::ended()
	{
		return state_ == PlayStatus::Status_end;
	}

	void AVPlayer::setVideoRefreshCallback(std::function<void(std::weak_ptr<VideoFrame>)> f)
	{
		videoRefreshCallback_ = f;
	}

	void AVPlayer::setSourceEndCallBack(std::function<void()> f)
	{
		sourceEndCallBack_ = f;
	}

	void AVPlayer::setProgressChangeCallBack(std::function<void(double)> f)
	{
		progressChangeCallBack_ = f;
	}

	void AVPlayer::demux()
	{
		if (!demuxer_)
			return;

		if (state_ == PlayStatus::Status_end)
		{
			return;
		}
		if (!demuxer_->readFrame())
		{
			demuxerThread_.stopTask();
			return;
		}
			
		Packet pkt = demuxer_->packet();
		const AVPacket* avpkt = pkt.asAVPacket(); 

		if (pkt.eof())
		{
			audioPackets.put(pkt, std::bind(&AVPlayer::ended, this));
			videoPackets.put(pkt, std::bind(&AVPlayer::ended, this));
			return;
		}

		if (avpkt->stream_index == parser_->audioStream())
		{
			audioPackets.put(pkt, std::bind(&AVPlayer::ended, this));
		}
		else if (avpkt->stream_index == parser_->videoStream())
		{
			videoPackets.put(pkt, std::bind(&AVPlayer::ended, this));
		}
	}

	void AVPlayer::decodeAudio()
	{
		if (!vdecoder_)
			return;

		Packet pkt;
		if (!audioPackets.tack(pkt, std::bind(&AVPlayer::ended, this)))
		{
			return;
		}
		if (pkt.eof())
		{
			AudioFrame frame;
			frame.setEof(true);
			audioFrames.put(frame, std::bind(&AVPlayer::ended, this));
			aDecoderThread_.stopTask();
			return;
		}

		if (adecoder_->decode(pkt))
		{
			AudioFrame frame = adecoder_->frame();
			audioFrames.put(frame, std::bind(&AVPlayer::ended, this));
		}
	}

	void AVPlayer::decodeVideo()
	{
		if (!vdecoder_)
			return;

		Packet pkt;
		if (!videoPackets.tack(pkt, std::bind(&AVPlayer::ended, this)))
		{
			return;
		}

		if (pkt.eof())
		{
			VideoFrame frame;
			frame.setEof(true);
			videoFrames.put(frame, std::bind(&AVPlayer::ended, this));
			vDecoderThread_.stopTask();
			return;
		}

		if (vdecoder_->decode(pkt))
		{
			VideoFrame frame = vdecoder_->frame();
			videoFrames.put(frame, std::bind(&AVPlayer::ended, this));
		}
	}

	void AVPlayer::renderVideo()
	{
		shared_ptr<VideoFrame> cache = std::make_shared<VideoFrame>();
		if (!videoFrames.tack(*cache, std::bind(&AVPlayer::ended, this)))
		{
			return;
		}
		
		if (cache->eof())
		{
			videoRenderThread_.stopTask();
			return;
		}
		if (videoRefreshCallback_)
			videoRefreshCallback_(cache);

		uint64 curTimeStampMSec = (uint64)(parser_->timebase() * cache->getTimeStampMsec() * 1000);
		uint64 stdtimestampMSec = clockmaster_msec_;

		int rate = parser_->framerate();
		int frame_durationMSec = 1000 / rate;

		if (curTimeStampMSec > stdtimestampMSec)
		{
			if ((curTimeStampMSec - stdtimestampMSec) <= frame_durationMSec)
				std::this_thread::sleep_for(std::chrono::milliseconds(frame_durationMSec));
			else
				std::this_thread::sleep_for(std::chrono::milliseconds(frame_durationMSec * 2));
		}
		else
		{
			if ((stdtimestampMSec - curTimeStampMSec) <= frame_durationMSec)
				std::this_thread::sleep_for(std::chrono::milliseconds(frame_durationMSec));
			else
				std::this_thread::sleep_for(std::chrono::milliseconds(frame_durationMSec / 2));
		}
		
	}


	void AVPlayer::renderAudio()
	{
		shared_ptr<AudioFrame> cache = std::make_shared<AudioFrame>();

		if (!audioFrames.tack(*cache, std::bind(&AVPlayer::ended, this)))
		{
			return;
		}
		if (cache->eof())
		{
			audioRenderThread_.stopTask();
			return;
		}
		for (; arender.QueueSize() >= 8;)
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(23));
		}
		arender.queue((void*)cache->data(), cache->getTimeStampMsec());
		arender.play();
	}

	void AVPlayer::startAllTask()
	{
		demuxerThread_.startTask(std::bind(&AVPlayer::demux, this));
		aDecoderThread_.startTask(std::bind(&AVPlayer::decodeAudio, this));
		vDecoderThread_.startTask(std::bind(&AVPlayer::decodeVideo, this));
		videoRenderThread_.startTask(std::bind(&AVPlayer::renderVideo, this));
		audioRenderThread_.startTask(std::bind(&AVPlayer::renderAudio, this));
	}

	void AVPlayer::stopAllTask()
	{
		demuxerThread_.stopTask();
		aDecoderThread_.stopTask();
		vDecoderThread_.stopTask();
		videoRenderThread_.stopTask();
		audioRenderThread_.stopTask();
		wakeAllThread();
		
	}

	void AVPlayer::clearAll()
	{
		audioPackets.clear();
		videoPackets.clear();
		audioFrames.clear();
		videoFrames.clear();
	}

	void AVPlayer::wakeAllThread()
	{
		audioPackets.wakeALL();
		videoPackets.wakeALL();
		audioFrames.wakeALL();
		videoFrames.wakeALL();
	}

	void AVPlayer::calcTime()
	{
		if (state_ != PlayStatus::Status_playing)
		{
			return;
		}

		//清除播放完的音频段，并根据音频段计算当前时间戳
		uint64 timestamp = arender.unqueue();
		if (0 != timestamp && clockmastertype_ == ClockMasterType::AudioMaster)
		{
			//double d = timestamp * parser_->timebase();
			clockmaster_msec_ = timestamp;
		}

		double duration = parser_->duration();
		if (progressChangeCallBack_)
			progressChangeCallBack_((double)clockmaster_msec_ / 1000 / duration);
		double a = fabs(duration - (double)clockmaster_msec_ / 1000);
		double b = ((double)1.0 / parser_->framerate() * 3);
		
		if (!videoRenderThread_.taskRunning())
		{
			if (progressChangeCallBack_)
				progressChangeCallBack_(1.0);
			if (sourceEndCallBack_)
				sourceEndCallBack_();
			state_ = PlayStatus::Status_end;
		}
		
	}

}