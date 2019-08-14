#ifndef MYVIDEOPLAYER_H
#define MYVIDEOPLAYER_H

#include <QThread>
#include <QImage>
#include "DecoderInterface.h"

class VideoDecoder : public DecoderInterface
{
public:
	explicit VideoDecoder(const std::string& strStreamFile);
    ~VideoDecoder();
    
	virtual void loop();

};

#endif // MYVIDEOPLAYER_H
