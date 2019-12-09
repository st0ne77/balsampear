#include "mainwindow.h"
#include "AVPlayer.h"
#include "PlayScreen.h"
using namespace std;
namespace balsampear
{
	MainWindow::MainWindow(QWidget* parent) :
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
		balsampear::PlayScreen* p = new balsampear::PlayScreen(&fullWidget_);
		p->setFramePorter(player_.getFramePorter());
		playArea_ = p;
		layout_.addWidget(playArea_, 9);
		layout_.addWidget(&button_, 1);

		connect(&button_, SIGNAL(clicked()), this, SLOT(play()));
		connect(&timer, SIGNAL(timeout()), this, SLOT(updateVideo()));

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
			player_.start();
		}

		timer.start(20);
	}
}


