#ifndef FRAME_H
#define FRAME_H
struct AVFrame;
class Frame
{
public:
	Frame();
	Frame(const char* pBuffer,int len, double pts);
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
	inline double Sec()
	{
		return mSec;
	}
private:
	char* mpBuffer;
	int mLen;
	double mSec;
};

#endif
