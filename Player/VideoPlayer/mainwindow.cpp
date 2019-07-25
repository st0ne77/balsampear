#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavutil/pixfmt.h"
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

///现在我们需要做的是让SaveFrame函数能把RGB信息定稿到一个PPM格式的文件中。
///我们将生成一个简单的PPM格式文件，请相信，它是可以工作的。
void SaveFrame(AVFrame *pFrame, int width, int height,int index)
{

  FILE *pFile;
  char szFilename[32];
  int  y;

  // Open file
  sprintf(szFilename, "frame%d.ppm", index);
  pFile=fopen(szFilename, "wb");

  if(pFile==NULL)
    return;

  // Write header
  fprintf(pFile, "P6%d %d255", width, height);

  // Write pixel data
  for(y=0; y<height; y++)
  {
    fwrite(pFrame->data[0]+y*pFrame->linesize[0], 1, width*3, pFile);
  }

  // Close file
  fclose(pFile);

}


void MainWindow::on_pushButton_clicked()
{
    av_register_all(); //初始化FFMPEG  调用了这个才能正常适用编码器和解码器

    //FFMPEG所有的操作都要通过AVFormatContext来进行
    AVFormatContext *pFormatCtx = avformat_alloc_context();

    //打开视频文件
    if (0 != avformat_open_input(&pFormatCtx, "D:\\Project\\TestFile\\Test.mp4", NULL, NULL))
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

    av_dump_format(pFormatCtx, 0, "D:\\Project\\TestFile\\Test.mp4", 0); //输出视频信息

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

                    SaveFrame(pFrameRGB, pCodecCtx->width,pCodecCtx->height,index++); //保存图片
                    if (index > 50)
                            return; //这里我们就保存50张图片
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
