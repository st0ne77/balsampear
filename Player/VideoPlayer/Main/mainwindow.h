#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "PlayWidget.h"
#include <QHBoxLayout>
#include <set>
#include <vector>
#include "ControlWidget.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
	void paintEvent(QPaintEvent* event);
	void dragEnterEvent(QDragEnterEvent* event);//拖动进入事件  

private:
	void releaseItem();

private:
	QWidget fullWidget_;
	QHBoxLayout hlayout_;
	QListWidget listWidget;
	QVBoxLayout vlayout_;
    PlayWidget playWidget_;
	ControlWidget controlWidget_;
	std::set<QString> listVideo_;
	std::vector<QListWidgetItem*> items_;

	
};

#endif // MAINWINDOW_H
