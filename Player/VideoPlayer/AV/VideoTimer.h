#ifndef PLAYINTERFACE_H
#define PLAYINTERFACE_H
#include <QTimer>

class VideoDecoder;
class AudioDecoder;
class PlayWidget;
class VideoTimer: public QTimer
{
	Q_OBJECT
public:
	explicit VideoTimer(VideoDecoder* pVDecoder, AudioDecoder *pADecoder, PlayWidget *pDrawWidget);

	virtual ~VideoTimer();

	void START(int msec);
	void STOP();
	void PAUSE();

signals:
	void ProgressChanged(int);

public slots:
	void update();

protected:
	VideoDecoder* mpVDecoder;
public:
	AudioDecoder* mpADecoder;
protected:
	PlayWidget* mpDrawWidget;
};

#endif // PLAYINTERFACE_H
