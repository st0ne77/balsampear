#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PlayWidget.h"
#include <QHBoxLayout>
#include <set>
#include <vector>
#include "ControlWidget.h"
#include "AVPlayer.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
	void dragEnterEvent(QDragEnterEvent* event);//拖动进入事件  

public slots:
	void checkChangePlayBtn();
	void sourceEnd();
private:
	void releaseItem();

private:
	QWidget fullWidget_;
	QHBoxLayout hlayout_;
	QListWidget listWidget;
	QVBoxLayout vlayout_;
    PlayWidget playWidget_;
	ControlWidget controlWidget_;
	AVPlayer player_;
	bool playing;
};

#endif // MAINWINDOW_H
