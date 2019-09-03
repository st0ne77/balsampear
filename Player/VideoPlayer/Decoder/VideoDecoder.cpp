#include "stdafx.h"
#include "VideoDecoder.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libswscale/swscale.h"
}

VideoDecoder::VideoDecoder(AVCodecContext* pAVCodecCtx)
	:AVDecoder(pAVCodecCtx)
	, mpSwsCtx(nullptr)
	, mpBuffer(nullptr)
	, mBytes(0)
{
	mpFrame = av_frame_alloc();
	mpFrameRGB = av_frame_alloc();
}

VideoDecoder::~VideoDecoder()
{
	if (mpBuffer)
	{
		av_free(mpBuffer);
	}
	av_frame_free(&mpFrame);
	av_frame_free(&mpFrameRGB);
}

bool VideoDecoder::init()
{
	bool ret = AVDecoder::init();
	if (ret)
	{
		mpSwsCtx = sws_getContext(mpAVCodecCtx->width, mpAVCodecCtx->height, mpAVCodecCtx->pix_fmt,
			mpAVCodecCtx->width, mpAVCodecCtx->height, AV_PIX_FMT_RGB24,
			SWS_BICUBIC, NULL, NULL, NULL);
		if (!mpSwsCtx)
		{
			ret = false;
		}
		else
		{
			mBytes = avpicture_get_size(AV_PIX_FMT_RGB24, mpAVCodecCtx->width, mpAVCodecCtx->height);
			mpBuffer = (uint8_t*)av_malloc(mBytes * sizeof(uint8_t));
			avpicture_fill((AVPicture*)mpFrameRGB, mpBuffer, AV_PIX_FMT_RGB24,
				mpAVCodecCtx->width, mpAVCodecCtx->height);

			
		}
	}
	return ret;
}

void VideoDecoder::decode()
{
	Packet pkt;
	mPktQueue.tack(pkt);
	
	int got_picture;
	int ret = avcodec_decode_video2(mpAVCodecCtx, mpFrame, &got_picture,pkt.getPacket());
	if (got_picture)
	{
		sws_scale(mpSwsCtx,
			(uint8_t const* const*)mpFrame->data,
			mpFrame->linesize, 0, mpAVCodecCtx->height, mpFrameRGB->data,
			mpFrameRGB->linesize);

		
		if (mpFrameRGB->linesize[0])
		{
// 			char* ch = new char[mpFrameRGB->linesize[0]];
// 			memset(ch, 0, mpFrameRGB->linesize[0]);
// 			if (memcmp(ch, mpFrameRGB->data[0], mpFrameRGB->linesize[0]))
// 			{
// 				int i = 0;
// 			}
			int sec = mpFrame->pts * av_q2d(mpAVCodecCtx->time_base);
			mFrameQueue.put(Frame((char*)mpFrameRGB->data[0], mBytes, sec));
		}
	}
}
