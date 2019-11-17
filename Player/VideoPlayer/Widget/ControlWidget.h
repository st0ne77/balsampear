#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include "AVPlayer.h"
class QHBoxLayout;
class ControlButton;
class ProgressWidget;
class OutDevice;
class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent, OutDevice* output);


	void play(const QString& video);
	void stop();
signals:

public slots:
	void changePlayStatus();
	void end();
protected:
	void paintEvent(QPaintEvent* event);

private:
	QHBoxLayout* mHBoxLayout;
	ProgressWidget* pProgressWidget_;
    ControlButton *mpControlButton;
	AVPlayer player;
	bool started_;
	bool mbPlying;
	int totaltime_;
};

#endif // CONTROLWIDGET_H
