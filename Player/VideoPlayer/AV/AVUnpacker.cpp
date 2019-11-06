#include "stdafx.h"
#include "AVUnpacker.h"
extern "C"
{
#include "libavformat/avformat.h"
}
#include "AudioDecoder.h"
#include "VideoDecoder.h"

AVUnpacker::AVUnpacker(const String& streamFile)
	:file_(streamFile),
	mpFormatCtx(nullptr),
	pADecoder(nullptr),
	pVDecoder(nullptr),
	AStreamIndex(-1),
	VStreamIndex(-1)
{
	init();
}

AVUnpacker::~AVUnpacker()
{
	delete pADecoder;
	pADecoder = nullptr;
	delete pVDecoder;
	pVDecoder = nullptr;
	avformat_close_input(&mpFormatCtx);
}

void AVUnpacker::Execute()
{
	AVPacket pkt;
	av_init_packet(&pkt);
	if (av_read_frame(mpFormatCtx, &pkt) >= 0)
	{
		if (pkt.stream_index == AStreamIndex)
		{
			while (!end_ && !pADecoder->putPacket(Packet(pkt), 100))
			{
			}
			
		}
		else if (pkt.stream_index == VStreamIndex)
		{
			while (!end_ && !pVDecoder->putPacket(Packet(pkt), 100))
			{
			}
		}
		av_packet_unref(&pkt);
	}
}

void AVUnpacker::init()
{
	av_register_all();//初始化FFMPEG  调用了这个才能正常适用编码器和解码器
	mpFormatCtx = avformat_alloc_context();//FFMPEG所有的操作都要通过AVFormatContext来进行

	//打开视频文件
	if (0 != avformat_open_input(&mpFormatCtx, file_.c_str(), NULL, NULL))
	{
		return;
	}

	if (avformat_find_stream_info(mpFormatCtx, NULL) < 0)
	{
		return;
	}
	av_dump_format(mpFormatCtx, 0, file_.c_str(), 0); //输出视频信息
	findDecoder();
}

void AVUnpacker::findDecoder()
{
	for (int i = 0; i < mpFormatCtx->nb_streams; ++i)
	{
		if (AVMEDIA_TYPE_AUDIO == mpFormatCtx->streams[i]->codec->codec_type)
		{
			AStreamIndex = i;
		}
		if (AVMEDIA_TYPE_VIDEO == mpFormatCtx->streams[i]->codec->codec_type)
		{
			VStreamIndex = i;
		}
	}

	AVCodecContext* pACodecCtx = AStreamIndex == -1? nullptr:mpFormatCtx->streams[AStreamIndex]->codec;
	AVCodecContext* pVCodecCtx = VStreamIndex == -1? nullptr:mpFormatCtx->streams[VStreamIndex]->codec;

	pADecoder = pACodecCtx == nullptr ? nullptr : new AudioDecoder(pACodecCtx);
	pVDecoder = pVCodecCtx == nullptr ? nullptr : new VideoDecoder(pVCodecCtx);
}


