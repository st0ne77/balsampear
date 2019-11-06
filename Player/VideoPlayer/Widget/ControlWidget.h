#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include "AVPlayer.h"
class QHBoxLayout;
class ControlButton;
class ProgressWidget;
class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent);


signals:

public slots:
	void changePlayStatus();
	void ProgressChanged(int progress);
protected:
	void paintEvent(QPaintEvent* event);

private:
	QHBoxLayout* mHBoxLayout;
	ProgressWidget* pProgressWidget_;
    ControlButton *mpControlButton;
	AVPlayer player;
	bool mbPlying;
	int totaltime_;
};

#endif // CONTROLWIDGET_H
