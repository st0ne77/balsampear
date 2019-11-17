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
	playWidget_(nullptr),
	controlWidget_(nullptr, (OutDevice*)&playWidget_)
{
    resize(800, 600);
	setCentralWidget(&fullWidget_);

	hlayout_.setContentsMargins(0, 0, 0, 0);//布局的四周外边距
	hlayout_.addWidget(&listWidget, 2);
	hlayout_.addLayout(&vlayout_, 8);
	vlayout_.setContentsMargins(0, 0, 0, 0);//布局的四周外边距
	vlayout_.addWidget(&playWidget_, 8);
	vlayout_.addWidget(&controlWidget_, 2);

	/*
	//setCentralWidget(this);
	
	
	*/

	const char* sheet = "QListWidget{background:black;};";
	listWidget.setStyleSheet(sheet);

	setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
	releaseItem();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
	QWidget::paintEvent(event);
	/*
	QPainter painter(this);
	painter.setBrush(Qt::black);
	painter.drawRect(0, 0, this->width(), this->height()); //先画成黑色 */ 
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
	QString str = event->mimeData()->urls()[0].toLocalFile();
	controlWidget_.stop();
	listVideo_.insert(str);

	
	releaseItem();
	std::set<QString>::iterator it = listVideo_.begin();
	for (;it != listVideo_.end(); ++it)
	{
		QListWidgetItem* item = new QListWidgetItem(*it);
		item->setBackground(Qt::white);
		item->setTextColor(Qt::red);
		listWidget.addItem(item);
		items_.push_back(item);
	}

	controlWidget_.play(str);
}

void MainWindow::releaseItem()
{
	std::vector<QListWidgetItem*>::iterator it = items_.begin();
	for (;it != items_.end(); ++it)
	{
		listWidget.removeItemWidget(*it);
		delete* it;
	}
	items_.clear();
}

