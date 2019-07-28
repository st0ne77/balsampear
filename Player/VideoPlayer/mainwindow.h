#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "playwidget.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    PlayWidget *mpPlayWidget;
};

#endif // MAINWINDOW_H
