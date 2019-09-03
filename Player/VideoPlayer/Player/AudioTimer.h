#ifndef AUDIOTIMER_H
#define AUDIOTIMER_H

#include <QTimer>

class AudioDecoder;
class AudioTimer:public QTimer
{
	Q_OBJECT
public:
	explicit AudioTimer(AudioDecoder*);

	virtual ~AudioTimer();

public slots:
	void update();

private:
	AudioDecoder* mpADecoder;
	int count;
};

#endif
