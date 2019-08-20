#include "stdafx.h"
#include "PlayerTimer.h"
#include "PlayWidget.h"
#include "DecoderInterface.h"
#include "DecoderFactory.h"

PlayerTimer::PlayerTimer(PlayWidget* pDrawWidget, const std::string& strStreamFile)
	:mpDrawWidget(pDrawWidget), mstrStreamFile(strStreamFile)
{
	mpDecoder = DecoderFactory::CreateDecoder(mstrStreamFile);
	if (mpDecoder)
	{
		mpDecoder->start();
	}

	connect(this, SIGNAL(timeout()), this, SLOT(update()));
}

PlayerTimer::~PlayerTimer()
{
	while (mpDecoder && (!mpDecoder->isFinished()))
	{
	}
	delete mpDecoder;
}

void PlayerTimer::StartPlay(int timer)
{
	if (mpDrawWidget && mpDecoder)
	{
		this->start(timer);
	}
}

void PlayerTimer::PausePlay()
{
	this->stop();
}

void PlayerTimer::StopPlay()
{
	this->stop();
	if (mpDecoder)
	{
		mpDecoder->stop();
	}
}

void PlayerTimer::update()
{
	if (mpDrawWidget && mpDecoder)
	{
		bool isValid = false;
		QImage img = mpDecoder->tack(isValid);
		if (isValid)
		{
			mpDrawWidget->Draw(img);
		}
		else
		{
			//this->stop();
		}
	}
}


