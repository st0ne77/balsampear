#include "myvideoplayer.h"
#include <QImage>
#include <QDebug>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/pixfmt.h"
}

MyVideoPlayer::MyVideoPlayer()
{

}


MyVideoPlayer::~MyVideoPlayer()
{

}



void MyVideoPlayer::run()
{
    char* filepath = "D:\\Project\\TestFile\\video.mp4";

    av_register_all(); //初始化FFMPEG  调用了这个才能正常适用编码器和解码器

    //FFMPEG所有的操作都要通过AVFormatContext来进行
    AVFormatContext *pFormatCtx = avformat_alloc_context();

    //打开视频文件
    if (0 != avformat_open_input(&pFormatCtx, filepath, NULL, NULL))
    {
        qDebug() << "open error.";
        return;
    }

    if (avformat_find_stream_info(pFormatCtx, NULL) < 0)
    {
        qDebug() <<"Could't find stream infomation.";
        return;
    }


    //找到视频流
    int firstvideostream = -1;
    for(int i = 0; i < pFormatCtx->nb_streams; ++i)
    {
        if(AVMEDIA_TYPE_VIDEO == pFormatCtx->streams[i]->codec->codec_type)
        {
            firstvideostream = i;
        }
    }

    //判断是否找到视频流
    if (-1 == firstvideostream)
    {
        qDebug() << "cannot find video stream.";
        return;
    }

    //查找解码器
    AVCodecContext *pCodecCtx = pFormatCtx->streams[firstvideostream]->codec;
    AVCodec *pCodec = avcodec_find_decoder(pCodecCtx->codec_id);

    if(NULL == pCodec)
    {
        qDebug() << "caonot find Codec.";
        return;
    }

    //打开解码器
    if (avcodec_open2(pCodecCtx , pCodec , NULL))
    {
        qDebug() << "cannot open codec";
        return;
    }


    AVFrame *pFrame = av_frame_alloc();
    AVFrame *pFrameRGB = av_frame_alloc();


    SwsContext *pSwsCtx = sws_getContext(pCodecCtx->width, pCodecCtx->height, pCodecCtx->pix_fmt,
                   pCodecCtx->width, pCodecCtx->height, AV_PIX_FMT_RGB24,
                   SWS_BICUBIC, NULL, NULL, NULL);

    int numBytes = avpicture_get_size(AV_PIX_FMT_RGB24, pCodecCtx->width, pCodecCtx->height);

    uint8_t *out_buffer = (uint8_t*)av_malloc(numBytes * sizeof(uint8_t));
    avpicture_fill((AVPicture *) pFrameRGB, out_buffer, AV_PIX_FMT_RGB24,
                pCodecCtx->width, pCodecCtx->height);

    int y_size = pCodecCtx->width * pCodecCtx->height;

    AVPacket* packet = (AVPacket *) malloc(sizeof(AVPacket)); //分配一个packet
    av_new_packet(packet, y_size); //分配packet的数据

    av_dump_format(pFormatCtx, 0, filepath, 0); //输出视频信息

    int index = 0;

    while (1)
    {
        if (av_read_frame(pFormatCtx, packet) < 0)
        {
            break; //这里认为视频读取完了
        }

        if (packet->stream_index == firstvideostream)
        {
            int got_picture;
            int ret = avcodec_decode_video2(pCodecCtx, pFrame, &got_picture,packet);

            if (ret < 0)
            {
                qDebug() <<"decode error.";
                return;
            }

            if (got_picture)
            {
                sws_scale(pSwsCtx,
                        (uint8_t const * const *) pFrame->data,
                        pFrame->linesize, 0, pCodecCtx->height, pFrameRGB->data,
                        pFrameRGB->linesize);

                QImage tmpImg((uint8_t*)pFrameRGB->data[0],pCodecCtx->width,pCodecCtx->height,QImage::Format_RGB888);
                QImage image = tmpImg.copy(); //把图像复制一份 传递给界面显示
                emit sig_GetOneFrame(image);  //发送信号


                msleep(30);
            }
        }
        av_free_packet(packet);
    }
    av_free(out_buffer);
    av_free(pFrameRGB);
    avcodec_close(pCodecCtx);
    avformat_close_input(&pFormatCtx);


    qDebug() << "end";
}
