#include "stdafx.h"
#include "DecoderInterface.h"

using namespace std;
DecoderInterface::DecoderInterface(const string& strStreamFile)
	:mbExit(false) , mstrSteamFile(strStreamFile)
{
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
		img = mCache.front();
		mCache.pop();
		result = true;
	}
	mMutex.unlock();
	return result;
}

void DecoderInterface::run()
{
	this->loop();
}

