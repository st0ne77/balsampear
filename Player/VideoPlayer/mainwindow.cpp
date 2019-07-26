#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myvideoplayer.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setMinimumSize(800, 400);
    setMaximumSize(800, 400);
    mpPlayWidget = new MyWidget(this);

    setCentralWidget(mpPlayWidget);

    MyVideoPlayer *videoplayer = new MyVideoPlayer();
    connect(videoplayer , SIGNAL(sig_GetOneFrame(QImage)), mpPlayWidget, SLOT(slotGetOneFrame(QImage)));
    videoplayer->start();
}

MainWindow::~MainWindow()
{

}




