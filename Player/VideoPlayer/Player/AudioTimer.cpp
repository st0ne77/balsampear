#include "stdafx.h"
#include "AudioTimer.h"
#include "AudioDecoder.h"

AudioTimer::AudioTimer(AudioDecoder* pDecoder)
	:mpADecoder(pDecoder)
	, count(0)
{
	connect(this, SIGNAL(timeout()), this, SLOT(update()));
}

AudioTimer::~AudioTimer()
{

}

void AudioTimer::update()
{
// 	++count;
// 	Frame frame = mpADecoder->popFrame();
// 	//if ( (count * 10)/1000 >= frame.Sec())
// 	{
// 		lvs_openal_interface_openaudiofromqueue(frame.Buffer(), frame.Len(), 44100, 16, 2);
// 	}
}
