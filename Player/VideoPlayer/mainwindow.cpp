#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myvideoplayer.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(800, 600);
    mpPlayWidget = new PlayWidget(this);//播放用Widget

    setCentralWidget(mpPlayWidget);

    MyVideoPlayer *videoplayer = new MyVideoPlayer();
    connect(videoplayer , SIGNAL(sig_GetOneFrame(QImage)), mpPlayWidget, SLOT(slotGetOneFrame(QImage)));
    videoplayer->start();
}

MainWindow::~MainWindow()
{
    delete mpPlayWidget;
}




