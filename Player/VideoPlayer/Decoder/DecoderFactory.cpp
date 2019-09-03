#include "stdafx.h"
#include "DecoderFactory.h"
#include "VideoDecoder.h"

DecoderInterface* DecoderFactory::CreateDecoder(const std::string& strStreamFile)
{
	return nullptr;// new VideoDecoder(strStreamFile);
}
