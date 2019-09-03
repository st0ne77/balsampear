#include "stdafx.h"
#include "VideoTimer.h"
#include "PlayWidget.h"
#include "Frame.h"
#include "VideoDecoder.h"
extern "C"
{
#include "SDL.h"
#include "libavutil/channel_layout.h"
#include "AudioDecoder.h"
}

double audioClock = 0;
void fun(void* userdata, Uint8* stream, int len)
{
	VideoTimer* pThis = (VideoTimer*)userdata;
	Frame frame = pThis->mpADecoder->popFrame();
	audioClock += frame.Sec();
	memcpy(stream, frame.Buffer(), frame.Len());
}

VideoTimer::VideoTimer(VideoDecoder* pVDecoder, AudioDecoder* pADecoder, PlayWidget* pDrawWidget)
	:mpVDecoder(pVDecoder)
	, mpADecoder(pADecoder)
	, mpDrawWidget(pDrawWidget)
{
	connect(this, SIGNAL(timeout()), this, SLOT(update()));

	SDL_AudioSpec wantSpec;
	memset(&wantSpec, 0, sizeof(SDL_AudioSpec));

	wantSpec.freq = 44100;
	wantSpec.format = AUDIO_S16SYS;
	wantSpec.channels = av_get_channel_layout_nb_channels(AV_CH_LAYOUT_STEREO);
	wantSpec.silence = 0;
	wantSpec.samples = 1024;
	wantSpec.callback = fun;
	wantSpec.userdata = this;

	if (SDL_Init(SDL_INIT_AUDIO))
	{
		printf("Could not initialize SDL - %s\n", SDL_GetError());
	}

	if (SDL_OpenAudio(&wantSpec, NULL) < 0)
	{
		printf("can not open SDL!\n");
		printf("Could not initialize SDL - %s\n", SDL_GetError());
	}

	
}

VideoTimer::~VideoTimer()
{

}


void VideoTimer::START(int msec)
{
	start(msec);
	SDL_PauseAudio(0);
}

void VideoTimer::STOP()
{
	stop();
	SDL_PauseAudio(1);
}

void VideoTimer::PAUSE()
{
	stop();
	SDL_PauseAudio(1);
}

void VideoTimer::update()
{
	Frame frame = mpVDecoder->popFrame();
	if (frame.Sec() > audioClock)
	{
		int delay = (frame.Sec() - audioClock + 40) * 1000;
		QThread::usleep(delay);
	}
	QImage tmpImg((uchar*)frame.Buffer(), 768, 432, QImage::Format_RGB888);
	mpDrawWidget->Draw(tmpImg.copy());
}


