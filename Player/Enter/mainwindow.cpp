#include "mainwindow.h"
#include "AVPlayer.h"
#include "OpenGLPlayWidget.h"
#include "ControlWidget.h"
using namespace std;
namespace balsampear
{
	MainWindow::MainWindow(QWidget* parent) :
		QMainWindow(parent),
		fullWidget_(this),
		layout_(&fullWidget_),
		player_()
	{
		//苦瓜播放器，0.1版本
		setWindowTitle("balsampear 0.1"); 
		resize(400, 300);
		setCentralWidget(&fullWidget_);

		layout_.setContentsMargins(0, 0, 0, 0);
		control_ = new ControlWidget(&fullWidget_);
		balsampear::OpenGLPlayWidget* p = new balsampear::OpenGLPlayWidget(&fullWidget_);
		p->setFramePorter(player_.getFramePorter());
		playArea_ = p;
		layout_.addWidget(playArea_, 9);
		layout_.addWidget(control_, 1);

		connect(control_, SIGNAL(checkChangePlayStatus()), this, SLOT(changePlayStatus()));
		connect(control_, SIGNAL(stopPlay()), this, SLOT(stopPlay()));
		connect(&timer, SIGNAL(timeout()), this, SLOT(updateVideo()));
		

		player_.load("E:\\Project\\TestFile\\110.mp4");
		player_.setSourceEndCallBack(std::bind(&MainWindow::sourceEndCallBack, this));
	}

	MainWindow::~MainWindow()
	{
		delete playArea_;
		playArea_ = nullptr;
	}

	void MainWindow::closeEvent(QCloseEvent* event)
	{
		
	}

	void MainWindow::updateVideo()
	{
		playArea_->update();
	}

	void MainWindow::changePlayStatus()
	{
		AVPlayer::PlayStatus curStatus = player_.status();
		if (curStatus != AVPlayer::PlayStatus::Status_playing)
		{
			player_.start();
			timer.start(20);//开启定时器刷新视频显示区
		}
		else
		{
			player_.pause();
			timer.stop();//关闭定时器，停止刷新视频显示区，减少gpu负载
		}

		//获取最新播放状态
		curStatus = player_.status();
		if (curStatus == AVPlayer::PlayStatus::Status_playing)
		{
			control_->setPlayingStatus(true);
		}
		else
		{
			control_->setPlayingStatus(false);
		}

		
	}

	void MainWindow::stopPlay()
	{
		player_.stop();
		playArea_->update();
		control_->setPlayingStatus(false);
		timer.stop();
	}

	void MainWindow::sourceEndCallBack()
	{
		control_->setPlayingStatus(false);
		playArea_->update();
		timer.stop();
	}

}


