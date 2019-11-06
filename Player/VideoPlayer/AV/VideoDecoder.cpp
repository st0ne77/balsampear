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
	initFormater();
}

VideoDecoder::~VideoDecoder()
{
	av_frame_free(&mpFrame);
	av_frame_free(&mpFrameRGB);
}

void VideoDecoder::initFormater()
{
	mpSwsCtx = sws_getContext(mpAVCodecCtx->width, mpAVCodecCtx->height, mpAVCodecCtx->pix_fmt,
		mpAVCodecCtx->width, mpAVCodecCtx->height, AV_PIX_FMT_RGB24,
		SWS_BICUBIC, NULL, NULL, NULL);
	if (mpSwsCtx)
	{
		mBytes = avpicture_get_size(AV_PIX_FMT_RGB24, mpAVCodecCtx->width, mpAVCodecCtx->height);
		mpBuffer = (uint8_t*)av_malloc(mBytes * sizeof(uint8_t));
		avpicture_fill((AVPicture*)mpFrameRGB, mpBuffer, AV_PIX_FMT_RGB24,
			mpAVCodecCtx->width, mpAVCodecCtx->height);
	}
}

void VideoDecoder::Execute()
{
	Packet pkt;
	mPktQueue.tack(pkt);

	int got_picture;
	int ret = avcodec_decode_video2(mpAVCodecCtx, mpFrame, &got_picture, pkt.getPacket());
	if (got_picture)
	{
		sws_scale(mpSwsCtx,
			(uint8_t const* const*)mpFrame->data,
			mpFrame->linesize, 0, mpAVCodecCtx->height, mpFrameRGB->data,
			mpFrameRGB->linesize);


		if (mpFrameRGB->linesize[0])
		{
			double sec = (double)av_frame_get_best_effort_timestamp(mpFrame);

			while (!end_ && !mFrameQueue.put(Frame((char*)mpFrameRGB->data[0], mBytes, sec), 100))
			{
			}
			
		}
	}
}
