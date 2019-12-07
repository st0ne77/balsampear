#include "mainwindow.h"
#include "AVPlayer.h"
#include "PlayScreen.h"
#include "VideoRenderFactory.h"
#include "OpenGLYUV420PRender.h"
PlayerCore::AVPlayer* playerXXX;
using namespace std;
using namespace PlayerCore;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    fullWidget_(this),
    layout_(&fullWidget_),
    player_()
{
    setWindowTitle("Video Player 0.1");
    resize(800, 600);
    setCentralWidget(&fullWidget_);

    layout_.setContentsMargins(0, 0, 0, 0);
    button_.setText("play");
    playArea_ = new PlayScreen(&fullWidget_);
    layout_.addWidget(playArea_, 9);
    layout_.addWidget(&button_, 1);

    connect(&button_, SIGNAL(clicked()), this, SLOT(play()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(updateVideo()));

    playerXXX = &player_;
}

MainWindow::~MainWindow()
{
    delete playArea_;
    playArea_ = nullptr;
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    player_.exit();
}

void MainWindow::updateVideo()
{
    playArea_->update();
}

void MainWindow::play()
{
    player_.load("E:\\Project\\TestFile\\video.mp4");
    if (player_.isLoaded())
    {
		std::shared_ptr<VideoRender> videoRender_ = make_shared<OpenGLYUV420PRender>();
		if (videoRender_)
		{
			videoRender_->init();
		}
        player_.setVideoRender(videoRender_);
        player_.start();

        dynamic_cast<PlayScreen*>(playArea_)->render__ = videoRender_;
    }
        
    timer.start(20);

	
}

