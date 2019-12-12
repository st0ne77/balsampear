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
#include "Base/Timer.h"

using std::shared_ptr;
using std::unique_ptr;

namespace balsampear
{
	class AVPlayer
	{
	public:
		enum class PlayStatus {Status_end, Status_playing, Status_pause, Status_wait};

		AVPlayer();
		~AVPlayer();
		bool load(const StringPiece& file);
		bool load();
		void unload();
		void setFile(const StringPiece& file);
		inline bool isLoaded() { return loaded; }
		void start();
		void pause();
		void stop();
		PlayStatus status();
		void setVideoRefreshCallback(std::function<void(std::weak_ptr<VideoFrame>)> f);
		void setSourceEndCallBack(std::function<void()> f);//播放完成回调
		void setProgressChangeCallBack(std::function<void(double)> f);//播放进度变化回调
	private:
		void demux();
		void decodeAudio();
		void decodeVideo();
		void renderVideo();
		void renderAudio();

		void startAllTask();
		void stopAllTask();
		void clearAll();
		void wakeAllThread();//唤醒所有操作队列的线程

		void calcTime();

	private:
		StringPiece file_;
		AVThread demuxerThread_;
		AVThread aDeocderThread_;
		AVThread vDecoderThread_;
		AVThread audioRenderThread_;
		AVThread videoRenderThread_;
		Timer standardTimer;
		uint64 standardTimeStamp_;
		BlockingQueue<Packet> audioPackets;
		BlockingQueue<Packet> videoPackets;
		BlockingQueue<AudioFrame> audioFrames;
		BlockingQueue<VideoFrame> videoFrames;
		unique_ptr<AVParser> parser_;
		unique_ptr<AVDemuxer> demuxer_;
		unique_ptr<AudioDecoder> adecoder_;
		unique_ptr<VideoDecoder> vdecoder_;
		std::function<void(std::weak_ptr<VideoFrame>)> videoRefreshCallback_;
		std::function<void()> sourceEndCallBack_;
		std::function<void(double)> progressChangeCallBack_;
		bool loaded;
		PlayStatus state_;
	};
}


