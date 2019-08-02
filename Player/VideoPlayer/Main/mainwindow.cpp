#include "stdafx.h"
#include "mainwindow.h"
#include "PlayWidget.h"
#include <string>

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    resize(800, 600);
	mpPlayWidget = new PlayWidget(this);//播放用Widget

	setCentralWidget(mpPlayWidget);
}

MainWindow::~MainWindow()
{
    delete mpPlayWidget;
}




