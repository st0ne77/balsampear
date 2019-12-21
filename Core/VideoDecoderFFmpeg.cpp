#include "VideoDecoderFFmpeg.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"
#include "libswscale/swscale.h"
}
#include "Packet.h"
#include "Base/MemoryPool.h"
namespace balsampear
{
	VideoDecoderFFmpeg::VideoDecoderFFmpeg()
		:avframe_(nullptr)
	{
		avframe_ = av_frame_alloc();
	}

	VideoDecoderFFmpeg::~VideoDecoderFFmpeg()
	{
		av_frame_free(&avframe_);
	}

	bool VideoDecoderFFmpeg::decode(const Packet& pkt)
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

			if (avframe_->width <= 0 || avframe_->height <= 0)
				return false;
			
			return true;
		}
		return false;
	}

	VideoFrame VideoDecoderFFmpeg::frame()
	{
		if (avframe_->width <= 0 || avframe_->height <=0 || !codecCtx_)
			return VideoFrame();

		VideoFrame f(avframe_);

		//rgb24测试代码
		
		/*content->data_.resize((size_t)avframe_->width * avframe_->height * 3);
		VideoFrame f(avframe_->width, avframe_->height, AV_PIX_FMT_RGB24, content);
		SwsContext* mpSwsCtx = sws_getContext(codecCtx_->width, codecCtx_->height, codecCtx_->pix_fmt,
			codecCtx_->width, codecCtx_->height, AV_PIX_FMT_RGB24,
			SWS_BICUBIC, NULL, NULL, NULL);
		Byte* p = &content->data_[0];
		int array[] = { 2304,0,0,0,0,0,0,0 };
		int ret = sws_scale(mpSwsCtx,
			(uint8_t const* const*)avframe_->data,
			avframe_->linesize, 0, avframe_->height, &p,
			array);*/
		f.setTimeStampMsec((uint64)avframe_->pts * timebase_ * 1000);
		return f;
	}

}


