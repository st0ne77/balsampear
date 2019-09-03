#ifndef FRAME_H
#define FRAME_H
struct AVFrame;
class Frame
{
public:
	Frame();
	Frame(const char* pBuffer,int len,int pts);
	Frame(const Frame& other);
	Frame& operator=(const Frame& other);
	virtual ~Frame();

	inline char* Buffer()
	{
		return mpBuffer;
	}
	inline int Len()
	{
		return mLen;
	}
	inline int Sec()
	{
		return mSec;
	}
private:
	char* mpBuffer;
	int mLen;
	int mSec;
};

#endif
