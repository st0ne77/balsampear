#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>

class QHBoxLayout;
class ControlButton;
class AVReader;
class AudioTimer;
class VideoTimer;
class ControlWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ControlWidget(QWidget *parent, AVReader *pAVReader);

signals:

public slots:
	void changePlayStatus();

private:
    QHBoxLayout *mHBoxLayout;//横向布局
    ControlButton *mpControlButton;
	AVReader* mpAVReader;
	AudioTimer* mpAudioTimer;
	VideoTimer* mpVideoTimer;
	bool mbPlying;
};

#endif // CONTROLWIDGET_H
