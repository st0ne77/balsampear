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
// QImage DecoderInterface::tack(bool& isValid)
// {
// 	QImage ret;
// 	return queue.tack(isValid, 10);
// }

void DecoderInterface::push(const QImage& img)
{
	queue.put(img);
}

void DecoderInterface::run()
{
	this->loop();
}

