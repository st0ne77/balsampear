#pragma once
#include <QObject>
#include "AVThread.h"

class AVUnpacker;
class AudioDecoder;
class VideoDecoder;
class PlayWidget;
class AVPlayer: public QObject
{
	Q_OBJECT
public:
	AVPlayer(PlayWidget*);
	AVPlayer(const string& path, PlayWidget*);
	void play(const string& path);
	void start();
	void pause();
	void stop();
	virtual ~AVPlayer();
signals:
	void ProgressChanged(int);

public slots:
	void update();

private:
	void initDevice();

	inline void releaseTask()
	{
		delete Unpacker_;
		Unpacker_ = nullptr;
	}
private:
	QTimer timer;
	PlayWidget* pwidget;
	AVThread unpackThread_;
	AVThread AudioDecodeThread_;
	AVThread VideoDecodeThread_;
	AVUnpacker *Unpacker_;
	AudioDecoder* ADecoder;
	VideoDecoder* VDecoder_;

	double audioClock_;
};