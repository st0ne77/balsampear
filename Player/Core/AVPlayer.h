#pragma once
#include "Base/StringPiece.h"
#include <memory>
#include <functional>

using std::shared_ptr;
using std::unique_ptr;

namespace PlayerCore
{
	class AVParser;
	class AVDemuxer;
	class AudioDecoder;
	class VideoDecoder;
	class AVPlayer
	{
	public:
		AVPlayer();
		AVPlayer(const StringPiece& file);
		bool load();
		void unload();
		inline bool isLoaded() { return loaded; }

	private:
		StringPiece file_;
		//AVThread demuxerThread_;
		//AVThread aDeocderThread_;
		//AVThread vDecoderThread_;
		unique_ptr<AVParser> parser_;
		shared_ptr<AVDemuxer> demuxer_;
		shared_ptr<AudioDecoder> adecoder_;
		shared_ptr<VideoDecoder> vdecoder_;
		std::function<void()> sourceEndCallBack;
		bool loaded;
	};
}


