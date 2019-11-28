#include "AVPlayer.h"
#include "AVParser.h"
namespace PlayerCore
{

	AVPlayer::AVPlayer()
		:loaded(false),
		demuxerThread_("demux thread"),
		aDeocderThread_("audio decode thread"),
		vDecoderThread_("video decode thread")
	{

	}

	AVPlayer::AVPlayer(const StringPiece& file)
		: loaded(false),
		file_(file),
		demuxerThread_("demux thread"),
		aDeocderThread_("audio decode thread"),
		vDecoderThread_("video decode thread")
	{
		load();
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
			adecoder_->setCodecContext(parser_->getAudioCodecCtx());
		}
		if (mediaType & 0x2)
		{
			vdecoder_ = VideoDecoder::create();
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
		demuxerThread_.startTask(std::bind(&AVPlayer::demux, this));
	}

	void AVPlayer::demux()
	{
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
			//videoPackets.put(pkt);
		}
	}

}