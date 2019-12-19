#include "AudioDeocderFFmpeg.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"
#include "libswscale/swscale.h"
#include "libswresample/swresample.h"
#include "libavutil/time.h"
}
#include "Packet.h"
#include "MemoryManager.h"
namespace balsampear
{
	
	AudioDeocderFFmpeg::AudioDeocderFFmpeg()
	{
		avframe_ = av_frame_alloc();
	}

	AudioDeocderFFmpeg::~AudioDeocderFFmpeg()
	{
		av_frame_free(&avframe_);
	}

	bool AudioDeocderFFmpeg::decode(const Packet& pkt)
	{
		if (codecCtx_)
		{
			int ret = avcodec_send_packet(codecCtx_, pkt.asAVPacket()); 
			if (ret)
				return false;//Error decoding video frame
			ret = avcodec_receive_frame(codecCtx_, avframe_);

			//前两帧会返回AVERROR(EAGAIN)
			if (ret)
				return false;

			

			
			return true;
		}
		return false;
	}
	SwrContext* mpSwrCtx = nullptr;
	AudioFrame AudioDeocderFFmpeg::frame()
	{
		//测试代码
// 		int test = av_frame_get_best_effort_timestamp(avframe_);
// 		int size = avframe_->nb_samples * av_get_bytes_per_sample(codecCtx_->sample_fmt) * avframe_->channels;
// 		int audioLen = av_samples_get_buffer_size(NULL, 2, avframe_->nb_samples, codecCtx_->sample_fmt, 1);
// 		double sec = (double)audioLen / (double)(2 * codecCtx_->channels * codecCtx_->sample_rate);

		//content->data_.resize(8192);
		//memcpy(&content->data_[0], avframe_->data[0], 8192);
		//if (!mpSwrCtx)
		{
			mpSwrCtx = swr_alloc();
			mpSwrCtx = swr_alloc_set_opts(mpSwrCtx,
				av_get_default_channel_layout(codecCtx_->channels),
				AV_SAMPLE_FMT_U8,
				codecCtx_->sample_rate,
				av_get_default_channel_layout(codecCtx_->channels),
				codecCtx_->sample_fmt,
				codecCtx_->sample_rate,
				0,
				NULL
			);
		}
		
		AudioFormat fmt = AudioFormat::create(codecCtx_->sample_fmt, (int)codecCtx_->channel_layout, codecCtx_->sample_rate);
		
		int bufferSize = av_samples_get_buffer_size(NULL, 2, avframe_->nb_samples, AV_SAMPLE_FMT_U8, 1);
		AudioFrame f(fmt);
		f.allocMemory(bufferSize);
		Byte* ptr = (Byte*)f.data();
		memset(ptr, 0, bufferSize);
		swr_init(mpSwrCtx);
		int convertSize = swr_convert(mpSwrCtx, &ptr,
			avframe_->nb_samples,
			(const uint8_t**)avframe_->extended_data, avframe_->nb_samples);
		sample_count_ += avframe_->nb_samples;
		uint64 timestamp_msec = sample_count_ * 1000 / avframe_->sample_rate;
		uint64 duration = avframe_->nb_samples * 1000 / avframe_->sample_rate;
		f.setTimeStampMsec(timestamp_msec);
		f.setDuration(duration);
		swr_free(&mpSwrCtx);
		return f;
	}

}