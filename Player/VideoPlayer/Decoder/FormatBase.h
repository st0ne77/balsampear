/*
*封装AVFormatContext结构及相关函数
*/

#ifndef FORMATBASE_H
#define FORMATBASE_H

#include <string>

struct AVFormatContext;
class AudioDecoder;
class VideoDecoder;
class FormatBase
{
public:
	FormatBase(const std::string& strStreamFile);

	virtual ~FormatBase();

	bool init();

	AudioDecoder* findAudioDecoder();
	VideoDecoder* findVideoDecoder();

	inline int audioStream() const
	{
		return maudioStream;
	}
	int videoStream() const
	{
		return mvideoStream;
	}

	bool readFrame();

private:
	AVFormatContext* mpFormatCtx;
	std::string mstrStreamFile;
	AudioDecoder* mpAudioDecoder;
	VideoDecoder* mpVideoDecoder;
	int maudioStream;
	int mvideoStream;
};

#endif
