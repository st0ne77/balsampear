#include "stdafx.h"
#include "Frame.h"
extern "C"
{
#include "libavutil/frame.h"
}


Frame::Frame(const char* pBuffer, int len, int sce)
	:mpBuffer(nullptr)
	, mLen(0)
	, mSec(sce)
{
	if (pBuffer && len)
	{
		mpBuffer = new char[len];
		memcpy(mpBuffer, pBuffer, len);
		mLen = len;
	}
}

Frame::Frame(const Frame& other)
	:mpBuffer(nullptr)
	, mLen(0)
	, mSec(0)
{
	if (this != &other)
	{
		if (other.mpBuffer && other.mLen)
		{
			mpBuffer = new char[other.mLen];
			memcpy(mpBuffer, other.mpBuffer, other.mLen);
			mLen = other.mLen;
			mSec = other.mSec;
		}
	}
}


Frame::Frame()
	:mpBuffer(nullptr)
	,mLen(0)
	,mSec(0)
{
}

Frame& Frame::operator=(const Frame& other)
{
	if (this != &other)
	{

		delete[] mpBuffer;
		mpBuffer = nullptr;
		mSec = other.mSec;
		if (other.mpBuffer && other.mLen)
		{
			mpBuffer = new char[other.mLen];
			memcpy(mpBuffer, other.mpBuffer, other.mLen);
			mLen = other.mLen;
			mSec = other.mSec;
		}
		else
		{
			mpBuffer = nullptr;
			mLen = 0;
		}
	}
	return *this;
}

Frame::~Frame()
{
	delete[] mpBuffer;
	mpBuffer = nullptr;
}

