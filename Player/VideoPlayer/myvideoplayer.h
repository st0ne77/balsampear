#ifndef MYVIDEOPLAYER_H
#define MYVIDEOPLAYER_H

#include <QThread>
#include <QImage>

class MyVideoPlayer : public QThread
{
    Q_OBJECT
public:
    ~MyVideoPlayer();

    static MyVideoPlayer *getInstance();
private:
    explicit MyVideoPlayer();

signals:
    void sig_GetOneFrame(QImage);
public slots:
    void ControlPlay(bool);

protected:
    void run();
private:
    static MyVideoPlayer *sing;
    bool mPlaying;
};

#endif // MYVIDEOPLAYER_H
