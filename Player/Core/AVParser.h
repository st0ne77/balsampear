#pragma once
#include "Base/StringPiece.h"
#include "AudioFormat.h"
#include "VideoFormat.h"
#include <memory>

using std::shared_ptr;
struct AVFormatContext;
struct AVCodecContext;

namespace PlayerCore
{
	class AVDemuxer;
	class AudioDecoder;
	class VideoDecoder;
	enum class MediaType 
	{
		Type_Invalid,
		Type_Audio,
		Type_Video,
		Type_AudioVideo,
	};
	class AVParser
	{
	public:
		AVParser();
		AVParser(const StringPiece& file);
		AVParser(const AVParser&) = delete;
		AVParser& operator= (const AVParser&) = delete;
		~AVParser();
		void setFile(const StringPiece& file);
		StringPiece currentFile() { return file_; }
		bool parse();
		inline unsigned long long getDuration() { return duration_; }
		inline AudioFormat getAudioFormat() { return aformat_; }
		inline VideoFormat getVideoFormat() { return vformat_; }

		inline int audioStream() { return aIndexOfStream_; }
		inline int videoStream() { return vIndexOfStream_; }
		

	private:
		StringPiece file_;
		AVFormatContext *formatCtx_;
		MediaType type_;
		unsigned long long duration_;
		AVCodecContext *aCodecCtx_;
		int aIndexOfStream_;
		AudioFormat aformat_;
		AVCodecContext *vCodecCtx_;
		int vIndexOfStream_;
		VideoFormat vformat_;
		shared_ptr<AVDemuxer> demuxer_;
		shared_ptr<AudioDecoder> adecoder;
		shared_ptr<VideoDecoder> vdecoder_;
	};
}


