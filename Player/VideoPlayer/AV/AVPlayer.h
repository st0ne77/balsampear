#pragma once
#include <QObject>
#include "AVThread.h"

class AVUnpacker;
class AudioDecoder;
class VideoDecoder;
class OutDevice;
class AVPlayer: public QObject
{
	Q_OBJECT
public:
	AVPlayer(OutDevice*);
	AVPlayer(const string& path, OutDevice*);
	void play(const string& path);
	void start();
	void pause();
	void stop();
	virtual ~AVPlayer();

	//获取但钱是否已有文件在解码播放
	bool running() { return Unpacker_ != nullptr; }
signals:
	void ProgressChanged(double);
	void sourceEnd();

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
	OutDevice* out_;
	AVThread unpackThread_;
	AVThread AudioDecodeThread_;
	AVThread VideoDecodeThread_;
	AVUnpacker *Unpacker_;
	AudioDecoder* ADecoder;
	VideoDecoder* VDecoder_;

	double audioClock_;
};