#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QVBoxLayout>

class PlayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PlayWidget(QWidget *parent = 0);

    ~PlayWidget();

signals:

public slots:
    void slotGetOneFrame(QImage);

protected:
    void paintEvent(QPaintEvent *event);
public:
    QVBoxLayout *mVLayout;
    QWidget *mEmptyWidget;
    QWidget *mProgressWidget;
    QImage mImage;
};

#endif // MYWIDGET_H
