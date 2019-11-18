#include "stdafx.h"
#include "mainwindow.h"
#include "PlayWidget.h"
#include <string>


using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
	fullWidget_(this),
	hlayout_(&fullWidget_),
	listWidget(&fullWidget_),
	playWidget_(&fullWidget_),
	controlWidget_(&fullWidget_),
	player_((OutDevice*)&playWidget_),
	playing(false)
{
    resize(800, 600);
	setCentralWidget(&fullWidget_);

	hlayout_.setContentsMargins(0, 0, 0, 0);//布局的四周外边距
	hlayout_.addWidget(&listWidget, 2);
	hlayout_.addLayout(&vlayout_, 8);
	vlayout_.setContentsMargins(0, 0, 0, 0);//布局的四周外边距
	vlayout_.addWidget(&playWidget_, 8);
	vlayout_.addWidget(&controlWidget_, 2);

	listWidget.setStyleSheet("background-color:black");

	connect(&controlWidget_, SIGNAL(checkChangePlayBtn()), this, SLOT(checkChangePlayBtn()));
	connect(&player_, SIGNAL(ProgressChanged(double)), &controlWidget_, SLOT(progressChanged(double)));
	connect(&player_, SIGNAL(sourceEnd()), this, SLOT(sourceEnd()));
	setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
	releaseItem();
}


void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
	QString str = event->mimeData()->urls()[0].toLocalFile();
	player_.play(str.toStdString());
	controlWidget_.setPlaying(playing = true);
}

void MainWindow::checkChangePlayBtn()
{
	if (player_.running())
	{
		playing = !playing;
		playing ? player_.start() : player_.pause();
		controlWidget_.setPlaying(playing);
	}
	
}

void MainWindow::sourceEnd()
{
	player_.stop();
	controlWidget_.setPlaying(playing = false);
}

void MainWindow::releaseItem()
{

}

