#ifndef PLAYINTERFACE_H
#define PLAYINTERFACE_H
#include <QTime>

class PlayWidget;
class DecoderInterface;
class PlayerTimer : public QTimer
{
	Q_OBJECT
public:
	explicit PlayerTimer(PlayWidget*pDrawWidget, const std::string& strStreamFile);

	virtual ~PlayerTimer();

	virtual void StartPlay(int timer);
	virtual void PausePlay();
	virtual void StopPlay();

public slots:
	void update();

protected:
	PlayWidget* mpDrawWidget;
	std::string mstrStreamFile;
	DecoderInterface* mpDecoder;
};

#endif // PLAYINTERFACE_H
