#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <string>
#include "OutDevice.h"


class ControlWidget;
class PlayWidget : public QWidget,virtual OutDevice
{
    Q_OBJECT
public:
    explicit PlayWidget(QWidget *parent);

    ~PlayWidget();

	virtual void Draw(const QImage& img);

protected:
    void paintEvent(QPaintEvent *event);
private:
	QImage mImage;
};

#endif // MYWIDGET_H
