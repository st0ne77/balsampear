#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

class MyWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0);

signals:

public slots:
    void slotGetOneFrame(QImage);

protected:
    void paintEvent(QPaintEvent *event);
public:
    QImage mImage;
};

#endif // MYWIDGET_H
