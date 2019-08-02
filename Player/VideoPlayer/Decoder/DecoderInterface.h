#ifndef DECODERINTERFACE_H 
#define DECODERINTERFACE_H
#include <QThread>
#include <queue>
#include <QImage>
#include <QMutex>

class DecoderInterface :public QThread
{
public:
	explicit DecoderInterface();

	virtual ~DecoderInterface();

	virtual void loop() = 0;

	void stop();

	bool FrontFrame(QImage& img);

private:
	void run();

protected:
	std::queue<QImage> mCache;
	bool mbExit;
	QMutex mMutex;
};
#endif //DECODERINTERFACE_H
