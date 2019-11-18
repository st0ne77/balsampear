#include "stdafx.h"
#include "AVPlayer.h"
#include "AVUnpacker.h"
#include "AudioDecoder.h"
#include "VideoDecoder.h"
extern "C"
{
#include "SDL.h"
#include "libavutil/channel_layout.h"
#include "PlayWidget.h"
}
AVPlayer::AVPlayer(const string& path, OutDevice* widget)
	:AVPlayer(widget)
{
	play(path);
}

AVPlayer::AVPlayer(OutDevice* widget)
	:out_(widget),
	Unpacker_(nullptr),
	ADecoder(nullptr),
	VDecoder_(nullptr),
	audioClock_(0)
{
	unpackThread_.setObjectName("unpackThread_");
	unpackThread_.start();
	AudioDecodeThread_.setObjectName("AudioDecodeThread_");
	AudioDecodeThread_.start();
	VideoDecodeThread_.setObjectName("VideoDecodeThread_");
	VideoDecodeThread_.start();
	initDevice();
}

void AVPlayer::play(const string& path)
{
	releaseTask();
	Unpacker_ = new AVUnpacker(path);
	ADecoder = Unpacker_->getADecoder();
	VDecoder_ = Unpacker_->getVDecoder();

	if (ADecoder)
	{
		AudioDecodeThread_.Start(ADecoder);
	}

	if (VDecoder_)
	{
		VideoDecodeThread_.Start(VDecoder_);
	}

	if (ADecoder || VDecoder_)
	{
		unpackThread_.Start(Unpacker_);
	}

	audioClock_ = 0;
	start();
}

void AVPlayer::start()
{
	AudioDecodeThread_.Start();
	VideoDecodeThread_.Start();
	unpackThread_.Start();

	if (Unpacker_ && ADecoder)
	{
		timer.start(30);
		SDL_PauseAudio(0);
	}
	
}

void AVPlayer::pause()
{
	AudioDecodeThread_.Pause();
	VideoDecodeThread_.Pause();
	unpackThread_.Pause();

	timer.stop();
	SDL_PauseAudio(1);
}

void AVPlayer::stop()
{
	timer.stop();
	SDL_PauseAudio(1);

	AudioDecodeThread_.Stop();
	VideoDecodeThread_.Stop();
	unpackThread_.Stop();
	releaseTask();
}

AVPlayer::~AVPlayer()
{
	timer.stop();
	SDL_CloseAudio();
	AudioDecodeThread_.Exit();
	VideoDecodeThread_.Exit();
	unpackThread_.Exit();

	while (AudioDecodeThread_.isRunning() || VideoDecodeThread_.isRunning() || unpackThread_.isRunning())
	{
	}
}

void AVPlayer::update()
{
	static Frame* pCache = NULL;
	if (NULL == pCache)
	{
		pCache = new Frame(VDecoder_->tackFrame());
	}
	if (pCache->Sec() > audioClock_)
	{
		return;
	}
	if (pCache->Sec() >= Unpacker_->getDuration())
	{
		emit sourceEnd();
	}
	QImage tmpImg((uchar*)pCache->Buffer(), 768, 432, QImage::Format_RGB888);
	out_->Draw(tmpImg.copy());
	delete pCache;
	pCache = NULL;
}

void AVPlayer::initDevice()
{
	connect(&timer, SIGNAL(timeout()), this, SLOT(update()));


	SDL_AudioSpec wantSpec;
	memset(&wantSpec, 0, sizeof(SDL_AudioSpec));

	wantSpec.freq = 44100;
	wantSpec.format = AUDIO_S16SYS;
	wantSpec.channels = av_get_channel_layout_nb_channels(AV_CH_LAYOUT_STEREO);
	wantSpec.silence = 0;
	wantSpec.samples = 1024;
	wantSpec.callback = [](void* userdata, Uint8* stream, int len)
	{
		AVPlayer* pThis = (AVPlayer*)userdata;
		Frame frame = pThis->ADecoder->tackFrame();
		pThis->audioClock_ += frame.Sec();
		memcpy(stream, frame.Buffer(), frame.Len());

		emit pThis->ProgressChanged(pThis->audioClock_ / pThis->Unpacker_->getDuration());
		
	};
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
