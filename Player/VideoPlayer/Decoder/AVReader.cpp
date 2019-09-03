#include "stdafx.h"
#include "AVReader.h"
#include "FormatBase.h"

extern "C"
{
#include <libavcodec/avcodec.h>
}

AVReader::AVReader(const std::string& strStreamFile)
	:mstrStreamFile(strStreamFile)
	, mpFormat(nullptr)
	, mpAudioDecoder(nullptr)
	, mpVideoDecoder(nullptr)
	, mbError(false)
{
	mpFormat = new FormatBase(mstrStreamFile);
	mbError = !mpFormat->init();
	if (!mbError)
	{
		mpAudioDecoder = mpFormat->findAudioDecoder();
		mpVideoDecoder = mpFormat->findVideoDecoder();
	}
}

AVReader::~AVReader()
{
	delete mpFormat;
	mpFormat = nullptr;
}

AudioDecoder* AVReader::getAudioDecoder()
{
	return mpAudioDecoder;
}

VideoDecoder* AVReader::getVideoDecoder()
{
	return mpVideoDecoder;
}


void AVReader::run()
{
	if (mbError)
	{
		return;
	}
	for (;;)
	{
		if (!mpFormat->readFrame())
		{
			break;
		}
	}
	
	
}
