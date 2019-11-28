#include "mainwindow.h"
#include "AVPlayer.h"


using namespace std;
using PlayerCore::AVPlayer;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setWindowTitle("Video Player 0.1");
    resize(800, 600);
    
    
    AVPlayer * player = new AVPlayer();
    if (player->load("E:\\Project\\TestFile\\video.mp4"))
        player->start();
}

MainWindow::~MainWindow()
{
}

