#include "stdafx.h"
#include "AudioDecoder.h"
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libswresample/swresample.h"
}
AudioDecoder::AudioDecoder(AVCodecContext* pAVCodecCtx)
	:AVDecoder(pAVCodecCtx)
	, mpSwrCtx(nullptr)
{
	initFormater();
}

void AudioDecoder::initFormater()
{
	mpSwrCtx = swr_alloc();

	mpSwrCtx = swr_alloc_set_opts(mpSwrCtx,
		av_get_default_channel_layout(mpAVCodecCtx->channels),
		AV_SAMPLE_FMT_S16,
		mpAVCodecCtx->sample_rate,
		av_get_default_channel_layout(mpAVCodecCtx->channels),
		mpAVCodecCtx->sample_fmt,
		mpAVCodecCtx->sample_rate,
		0,
		NULL
	);
}


void AudioDecoder::Execute()
{
	Packet pkt;
	mPktQueue.tack(pkt);

	AVFrame* pSrcFrame = av_frame_alloc();
	int got_frame_ptr;
	AVPacket* pAVPkt = pkt.getPacket();
	int pktSize = pAVPkt->size;
	for (; pktSize > 0;)
	{
		//解码
		int decodeSize = avcodec_decode_audio4(mpAVCodecCtx, pSrcFrame, &got_frame_ptr, pAVPkt);
		if (decodeSize < 0)
		{
			break;;
		}
		pktSize -= decodeSize;

		if (got_frame_ptr > 0)
		{
			unsigned char* pcm = new unsigned char[192000 * 4];
			uint8_t* arr[2] = { 0 };
			arr[0] = pcm;
			//重采样
			swr_init(mpSwrCtx);
			int convertSize = swr_convert(mpSwrCtx, arr,
				pSrcFrame->nb_samples,
				(const uint8_t**)pSrcFrame->extended_data, pSrcFrame->nb_samples);

			if (convertSize > 0)
			{
				int test = av_frame_get_best_effort_timestamp(pSrcFrame);
				int size = pSrcFrame->nb_samples * av_get_bytes_per_sample(AV_SAMPLE_FMT_S16) * pSrcFrame->channels;
				int audioLen = av_samples_get_buffer_size(NULL, 2, pSrcFrame->nb_samples, AV_SAMPLE_FMT_S16, 1);
				double sec = (double)audioLen /(double)(2 * mpAVCodecCtx->channels * mpAVCodecCtx->sample_rate);
				while (!end_ && !mFrameQueue.put(Frame((char*)pcm, size, sec), 100))
				{
				}
				
			}
			delete[] pcm;
		}


	}
	av_frame_free(&pSrcFrame);
}
