# pragma warning (disable:4819)
#include "VideoDecoderFFmpeg.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavutil/imgutils.h"
#include "libswscale/swscale.h"
}
#include "Packet.h"
namespace PlayerCore
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


		shared_ptr<Frame::Content> content = std::make_shared<Frame::Content>();
		content->data_.resize(avframe_->width * avframe_->height * 4);

		VideoFrame f(avframe_->width, avframe_->height, codecCtx_->pix_fmt, content);
		f.y.resize(avframe_->width * avframe_->height);
		f.u.resize(avframe_->width * avframe_->height / 4);
		f.v.resize(avframe_->width * avframe_->height / 4);
		memcpy(&f.y[0], avframe_->data[0], avframe_->width * avframe_->height);
		memcpy(&f.u[0], avframe_->data[1], avframe_->width * avframe_->height / 4);
		memcpy(&f.v[0], avframe_->data[2], avframe_->width * avframe_->height / 4);

		SwsContext *mpSwsCtx = sws_getContext(codecCtx_->width, codecCtx_->height, codecCtx_->pix_fmt,
			codecCtx_->width, codecCtx_->height, AV_PIX_FMT_RGB24,
			SWS_BICUBIC, NULL, NULL, NULL);
		Byte* p = &content->data_[0];
		int array[] = { 2304,0,0,0,0,0,0,0 };
		int ret = sws_scale(mpSwsCtx,
			(uint8_t const* const*)avframe_->data,
			avframe_->linesize, 0, avframe_->height, &p,
			array);

		return f;
	}

}


