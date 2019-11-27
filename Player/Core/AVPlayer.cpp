#include "AVPlayer.h"
#include "AVParser.h"
#include "AVDemuxer.h"
#include "AudioDecoder.h"
#include "VideoDecoder.h"
namespace PlayerCore
{

	AVPlayer::AVPlayer()
		:loaded(false)
	{

	}

	AVPlayer::AVPlayer(const StringPiece& file)
		: loaded(false),
		file_(file)
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
		return true;
	}

	void AVPlayer::unload()
	{
		parser_ = nullptr;
		demuxer_ = nullptr;
		adecoder_ = nullptr;
		vdecoder_ = nullptr;
	}

}