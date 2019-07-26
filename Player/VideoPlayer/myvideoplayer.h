#ifndef MYVIDEOPLAYER_H
#define MYVIDEOPLAYER_H

#include <QThread>
#include <QImage>

class MyVideoPlayer : public QThread
{
    Q_OBJECT
public:
    explicit MyVideoPlayer();

    ~MyVideoPlayer();
signals:
    void sig_GetOneFrame(QImage);
protected:
    void run();
};

#endif // MYVIDEOPLAYER_H
