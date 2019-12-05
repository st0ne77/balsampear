#pragma once
#include "Base/StringPiece.h"
#include <memory>
#include <functional>
#include "AVThread.h"
#include "Base/BlockingQueue.h"
#include "Packet.h"
#include "AVParser.h"
#include "AVDemuxer.h"
#include "AudioDecoder.h"
#include "VideoDecoder.h"

using std::shared_ptr;
using std::unique_ptr;

namespace PlayerCore
{
	class AVPlayer
	{
	public:
		enum class PlayStatus {Status_end, Status_playing, Status_pause, Status_wait};

		AVPlayer();
		AVPlayer(const StringPiece& file);
		bool load(const StringPiece& file);
		bool load();
		void unload();
		void setFile(const StringPiece& file);
		inline bool isLoaded() { return loaded; }

		void start();

		void demux();
		void decodeAudio();
		void decodeVideo();


		BlockingQueue<VideoFrame> videoFrames;
	private:
		StringPiece file_;
		AVThread demuxerThread_;
		AVThread aDeocderThread_;
		AVThread vDecoderThread_;
		BlockingQueue<Packet> audioPackets;
		BlockingQueue<Packet> videoPackets;
		unique_ptr<AVParser> parser_;
		unique_ptr<AVDemuxer> demuxer_;
		unique_ptr<AudioDecoder> adecoder_;
		unique_ptr<VideoDecoder> vdecoder_;
		std::function<void()> sourceEndCallBack;
		bool loaded;
		PlayStatus state_;
	};
}


