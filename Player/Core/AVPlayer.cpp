#include "AVPlayer.h"
#include "AudioRenderer.h"
#include <iostream>

namespace balsampear
{
	AudioRenderer arender;
	AVPlayer::AVPlayer()
		:loaded(false),
		demuxerThread_("demux thread"),
		aDeocderThread_("audio decode thread"),
		vDecoderThread_("video decode thread"),
		videoRenderThread_("render thread"),
		audioRenderThread_("audio render thread"),
		standardTimeStamp_(0),
		porter_(new FramePorter()),
		state_(PlayStatus::Status_end)
	{
		arender.init();
		standardTimer.start(5, std::bind(&AVPlayer::calcTime, this));
	}

	AVPlayer::~AVPlayer()
	{
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
		stopAllTask();
		state_ = PlayStatus::Status_end;
		clearAll();
		wakeAllThread();
		shared_ptr<VideoFrame> empty;
		porter_->updateVideoFrame(empty);

		unload();
		standardTimeStamp_ = 0;//重置标准时间
	}

	balsampear::AVPlayer::PlayStatus AVPlayer::status()
	{
		return state_;
	}

	shared_ptr<balsampear::FramePorter> AVPlayer::getFramePorter()
	{
		return porter_;
	}

	void AVPlayer::setSourceEndCallBack(std::function<void()> f)
	{
		sourceEndCallBack = f;
	}

	void AVPlayer::setProgressChangeCallBack(std::function<void(double)> f)
	{
		progressChangeCallBack = f;
	}

	void AVPlayer::demux()
	{
		if (!demuxer_)
			return;
		if (!demuxer_->readFrame())
		{
			demuxerThread_.stopTask();
			return;
		}
			
		Packet pkt = demuxer_->packet();
		const AVPacket* avpkt = pkt.asAVPacket(); 
		if (avpkt->stream_index == parser_->audioStream())
		{
			while (!audioPackets.put(pkt, 10))
			{
				if (state_ == PlayStatus::Status_end)
				{
					return;
				}
			}
		}
		else if (avpkt->stream_index == parser_->videoStream())
		{
			while (!videoPackets.put(pkt, 10))
			{
				if (state_ == PlayStatus::Status_end)
				{
					return;
				}
			}
		}
	}

	void AVPlayer::decodeAudio()
	{
		if (!vdecoder_)
			return;

		Packet pkt;
		while (!audioPackets.tack(pkt, 10))
		{
			if (state_ == PlayStatus::Status_end)
			{
				return;
			}
			if (!demuxerThread_.taskRunning())
			{
				aDeocderThread_.stopTask();
				return;
			}
		}

		if (adecoder_->decode(pkt))
		{
			AudioFrame frame = adecoder_->frame();
			while (!audioFrames.put(frame, 10))
			{
				if (state_ == PlayStatus::Status_end)
				{
					return;
				}
			}
		}
	}

	void AVPlayer::decodeVideo()
	{
		if (!vdecoder_)
			return;

		Packet pkt;
		while (!videoPackets.tack(pkt, 10))
		{
			if (state_ == PlayStatus::Status_end)
			{
				return;
			}
			if (!demuxerThread_.taskRunning())
			{
				vDecoderThread_.stopTask();
				return;
			}
		}

		if (vdecoder_->decode(pkt))
		{
			VideoFrame frame = vdecoder_->frame();
			while (!videoFrames.put(frame, 10))
			{
				if (state_ == PlayStatus::Status_end)
				{
					return;
				}
			}
		}
	}

	void AVPlayer::renderVideo()
	{
		shared_ptr<VideoFrame> cache = std::make_shared<VideoFrame>();
		while (!videoFrames.tack(*cache, 10))
		{
			if (state_ == PlayStatus::Status_end)
			{
				return;
			}

			if (!vDecoderThread_.taskRunning())
			{
				videoRenderThread_.stopTask();
			}
		} 
		porter_->updateVideoFrame(cache);

		double curTimeStampMSec = parser_->timebase() * cache->getTimeStampMsec() * 1000;
		double stdtimestampMSec = standardTimeStamp_;

		int rate = parser_->framerate();
		int frame_durationMSec = 1000 / rate;
		//std::cout << "frame_timestamp:"  << curTimeStampMSec <<std::endl;
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
		while (!audioFrames.tack(*cache, 10))
		{
			if (state_ == PlayStatus::Status_end)
			{
				return;
			}
			if (!audioRenderThread_.taskRunning())
			{
				audioRenderThread_.stopTask();
			}
		}
		while (arender.queuedFrameNum() >= 8)
		{
			arender.unqueue();
			std::this_thread::sleep_for(std::chrono::milliseconds(22));
		}
		//arender.update((void*)cache->data());
		//arender.play();
	}

	void AVPlayer::startAllTask()
	{
		demuxerThread_.startTask(std::bind(&AVPlayer::demux, this));
		aDeocderThread_.startTask(std::bind(&AVPlayer::decodeAudio, this));
		vDecoderThread_.startTask(std::bind(&AVPlayer::decodeVideo, this));
		videoRenderThread_.startTask(std::bind(&AVPlayer::renderVideo, this));
		audioRenderThread_.startTask(std::bind(&AVPlayer::renderAudio, this));
	}

	void AVPlayer::stopAllTask()
	{
		demuxerThread_.stopTask();
		aDeocderThread_.stopTask();
		vDecoderThread_.stopTask();
		videoRenderThread_.stopTask();
		audioRenderThread_.stopTask();
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

		int duration = parser_->duration();
		standardTimeStamp_ += 5;
		if (progressChangeCallBack)
			progressChangeCallBack((double)standardTimeStamp_ / 1000 / duration);
		if ( (standardTimeStamp_ / 1000 - duration)<=0.05)
		{
			state_ = PlayStatus::Status_end;
			standardTimeStamp_ = 0;
			if (sourceEndCallBack)
			{
				sourceEndCallBack();//todo 这里直接结束，会导致最后一帧刷新不出来
			}
		}

	}

}