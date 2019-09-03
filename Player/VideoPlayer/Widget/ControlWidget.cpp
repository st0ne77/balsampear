#include "stdafx.h"
#include "ControlWidget.h"
#include "ControlButton.h"
#include <QHBoxLayout>
#include "PlayWidget.h"
#include "VideoTimer.h"
#include "AudioTimer.h"
#include "AVReader.h"
#include "AudioDecoder.h"
#include "VideoDecoder.h"

ControlWidget::ControlWidget(QWidget* parent, AVReader* pAVReader)
	:
	QWidget(parent),
	mpAVReader(pAVReader),
	mpAudioTimer(nullptr),
	mpVideoTimer(nullptr),
	mbPlying(false),
	mHBoxLayout(new QHBoxLayout(this)),
	mpControlButton(new ControlButton(this))

{
	mHBoxLayout->addWidget(new QWidget(), 9);
    mHBoxLayout->addWidget(mpControlButton, 2);
    mHBoxLayout->addWidget(new QWidget(), 9);

	AudioDecoder *pADecoder = mpAVReader->getAudioDecoder();
	VideoDecoder* pVDecoder = mpAVReader->getVideoDecoder();

	

	PlayWidget *pPlayWidget = dynamic_cast<PlayWidget*>(parent);

	mpAVReader->start();
	if (mpAVReader->isRunning())
	{
		pADecoder->start();
		if (pPlayWidget)
		{
			pVDecoder->start();
		}
		
	}

	mpAudioTimer = new AudioTimer(pADecoder);
	if (pPlayWidget)
	{
		mpVideoTimer = new VideoTimer(pVDecoder, pADecoder, pPlayWidget);
	}

	connect(mpControlButton, SIGNAL(clicked()), this, SLOT(changePlayStatus()));
}

void ControlWidget::changePlayStatus()
{
	if (mbPlying)
	{
		if (mpAudioTimer)
		{
			//mpAudioTimer->stop();
		}
		if (mpVideoTimer)
		{
			mpVideoTimer->STOP();
		}
		mbPlying = false;
	}
	else
	{
		if (mpAudioTimer)
		{
			//mpAudioTimer->start(10);
		}
		if (mpVideoTimer)
		{
			mpVideoTimer->START(30);
		}
		mbPlying = true;
	}
}


