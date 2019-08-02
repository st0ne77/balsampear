#include "stdafx.h"
#include "DecoderInterface.h"

DecoderInterface::DecoderInterface()
{
	mbExit = false;
}

DecoderInterface::~DecoderInterface()
{

}

void DecoderInterface::stop()
{
	mbExit = true;
}

bool DecoderInterface::FrontFrame(QImage& img)
{
	bool result = false;
	mMutex.lock();
	if (!mCache.empty())
	{
		mCache.front();
		mCache.pop();
	}
	mMutex.unlock();
	return result;
}

void DecoderInterface::run()
{
	this->loop();
}

