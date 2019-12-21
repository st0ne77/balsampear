#include "AVParser.h"

#pragma warning(disable: 4819)
extern "C"
{
#include "libavformat/avformat.h"
}
#include "AVDemuxer.h"
#include "AudioDecoder.h"
#include "VideoDecoder.h"

namespace balsampear
{
	AVParser::AVParser()
		:formatCtx_(nullptr),
		type_ (0),
		duration_(0.0),
		aCodecCtx_(nullptr),
		aIndexOfStream_(-1),
		vCodecCtx_(nullptr),
		vIndexOfStream_(-1),
		videoTimeBase_(0),
		framerate_(0)
	{
		avformat_network_init();
	}

	AVParser::AVParser(const StringPiece& file)
		:AVParser()
	{
		setFile(file);
	}

	AVParser::~AVParser()
	{
		//Free it and all its contents and set *s to NULL.
		avformat_close_input(&formatCtx_);
	}

	void AVParser::setFile(const StringPiece& file)
	{
		file_ = file;
	}

	balsampear::StringPiece AVParser::currentFile()
	{
		return file_;
	}

	bool AVParser::parse()
	{
		// stream file
		//todo net
		formatCtx_ = avformat_alloc_context();
		if (!formatCtx_)
			return false;
		if (0 != avformat_open_input(&formatCtx_, file_.c_str(), NULL, NULL))
			return false;
		if (avformat_find_stream_info(formatCtx_, NULL) < 0)
			return false;

		for (unsigned int index = 0; index < formatCtx_->nb_streams; ++index)
		{
			AVCodecParameters *codecpar = formatCtx_->streams[index]->codecpar;
			if (AVMEDIA_TYPE_AUDIO == codecpar->codec_type)
			{
				aIndexOfStream_ = index;
				aCodecCtx_ = avcodec_alloc_context3(NULL);
				if (!aCodecCtx_)
					return false;
				avcodec_parameters_to_context(aCodecCtx_, codecpar);
			}
				
			if (AVMEDIA_TYPE_VIDEO == codecpar->codec_type)
			{
				vIndexOfStream_ = index;
				vCodecCtx_ = avcodec_alloc_context3(NULL);
				if (!vCodecCtx_)
					return false;
				avcodec_parameters_to_context(vCodecCtx_, codecpar);
			}
		}

		if (aCodecCtx_)
		{
			aformat_.setSampleRate(aCodecCtx_->sample_rate);
			type_ |= static_cast<int>(MediaType::Type_Audio);
		}
		if (vCodecCtx_)
		{
			vformat_ = VideoFormat(vCodecCtx_->pix_fmt);
			type_ |= static_cast<int>(MediaType::Type_Video);
		}
		duration_ = (double)formatCtx_->duration/ 1000000;
		videoTimeBase_ = av_q2d(formatCtx_->streams[vIndexOfStream_]->time_base);
		audioTimeBase_ = av_q2d(formatCtx_->streams[aIndexOfStream_]->time_base);


		framerate_ = (int)av_q2d(formatCtx_->streams[vIndexOfStream_]->avg_frame_rate);
		return true;
	}

	AVFormatContext* AVParser::getFormatCtx()
	{
		return formatCtx_;
	}

	AVCodecContext* AVParser::getAudioCodecCtx()
	{
		return aCodecCtx_;
	}

	AVCodecContext* AVParser::getVideoCodexCtx()
	{
		return vCodecCtx_;
	}

	double AVParser::duration()
	{
		return duration_;
	}

	AudioFormat AVParser::getAudioFormat()
	{
		return aformat_;
	}

	VideoFormat AVParser::getVideoFormat()
	{
		return vformat_;
	}

	int AVParser::getMediaType()
	{
		return type_;
	}

	double AVParser::videotimebase()
	{
		return videoTimeBase_;
	}

	double AVParser::audeiotimebase()
	{
		return audioTimeBase_;
	}

	int AVParser::framerate()
	{
		return framerate_;
	}

	int AVParser::audioStream()
	{
		return aIndexOfStream_;
	}

	int AVParser::videoStream()
	{
		return vIndexOfStream_;
	}

}

