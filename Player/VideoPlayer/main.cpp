#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

extern "C"
{
#include "libavcodec/avcodec.h"
#include <libavformat/avformat.h>
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
}


int main(int argc, char *argv[])
{
    //这里简单的输出一个版本号
    qDebug() << "Hello FFmpeg!" << endl;
    av_register_all();
    unsigned version = avcodec_version();
    qDebug() << "version is:" << version;


    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
