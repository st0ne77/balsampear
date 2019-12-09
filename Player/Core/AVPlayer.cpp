# pragma warning (disable:4819)
#include "AVPlayer.h"
namespace balsampear
{

	AVPlayer::AVPlayer()
		:loaded(false),
		demuxerThread_("demux thread"),
		aDeocderThread_("audio decode thread"),
		vDecoderThread_("video decode thread"),
		renderThread_("render thread"),
		porter_(new FramePorter()),
		state_(PlayStatus::Status_end)
	{

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

	void AVPlayer::exit()
	{
		stopAllTask();
	}

	shared_ptr<balsampear::FramePorter> AVPlayer::getFramePorter()
	{
		return porter_;
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
			//audioPackets.put(pkt);
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
		stopAllTask();
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

	void AVPlayer::render()
	{
		shared_ptr<VideoFrame> cache = std::make_shared<VideoFrame>();
		while (!videoFrames.tack(*cache, 10))
		{
			if (state_ == PlayStatus::Status_end)
			{
				return;
			}
		} 
		porter_->updateVideoFrame(cache);

		int rate = 0;
		if (rate = parser_->framerate())
			std::this_thread::sleep_for(std::chrono::milliseconds(1000/ rate));
		else
			std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}

	void AVPlayer::startAllTask()
	{
		demuxerThread_.startTask(std::bind(&AVPlayer::demux, this));
		vDecoderThread_.startTask(std::bind(&AVPlayer::decodeVideo, this));
		renderThread_.startTask(std::bind(&AVPlayer::render, this));
	}

	void AVPlayer::stopAllTask()
	{
		demuxerThread_.stopTask();
		aDeocderThread_.stopTask();
		vDecoderThread_.stopTask();
		renderThread_.stopTask();
	}

}