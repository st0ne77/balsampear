#ifndef AVREADER_H
#define AVREADER_H
#include <string>

class AudioDecoder;
class VideoDecoder;
struct FormatBase;
class AVReader : public QThread
{
public:
	AVReader(const std::string& strStreamFile);

	virtual ~AVReader();

	AudioDecoder* getAudioDecoder();
	VideoDecoder* getVideoDecoder();

private:

protected:
	virtual void run();
private:
	std::string mstrStreamFile;
	FormatBase* mpFormat;
	AudioDecoder* mpAudioDecoder;
	VideoDecoder* mpVideoDecoder;
	bool mbError;
};


#endif
