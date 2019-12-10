#include "AudioRenderer.h"
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
namespace balsampear
{

	AudioRenderer::AudioRenderer()
	{

	}

	AudioRenderer::~AudioRenderer()
	{

	}


	// 源声音的位置
	ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };

	// 源声音的速度
	ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };

	// 听者的位置
	ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };

	// 听者的速度
	ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };

	// 听者的方向 (first 3 elements are "at", second 3 are "up")
	ALfloat ListenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

	// 存储声音数据
	ALuint Buffer;

	// 用于播放声音
	ALuint Source;

	void AudioRenderer::init()
	{
		//打开device
		ALCdevice* m_Devicde = alcOpenDevice(nullptr);
		if (m_Devicde)
		{
			//建立声音文本描述
			ALCcontext *m_Context = alcCreateContext(m_Devicde, nullptr);

			//设置行为文本描述
			alcMakeContextCurrent(m_Context);
		}
		// 捆绑源
		alGenSources(1, &Source);

		if (alGetError() != AL_NO_ERROR)
			return ;

		
	
		alSourcef(Source, AL_PITCH, 1.0f);
		alSourcef(Source, AL_GAIN, 1.0f);
		alSourcefv(Source, AL_POSITION, SourcePos);
		alSourcefv(Source, AL_VELOCITY, SourceVel);
		alSourcei(Source, AL_LOOPING, AL_FALSE);
		

		// 做错误检测并返回
		if (alGetError() != AL_NO_ERROR)
			return ;

		alListenerfv(AL_POSITION, ListenerPos);
		alListenerfv(AL_VELOCITY, ListenerVel);
		alListenerfv(AL_ORIENTATION, ListenerOri);
		
	}

	void AudioRenderer::play()
	{
		alSourcePlay(Source);
	}

	void AudioRenderer::update(void* data)
	{
		
		alGenBuffers(1, &Buffer);
		if (alGetError() != AL_NO_ERROR)
			return;
		alBufferData(Buffer, AL_FORMAT_STEREO8, data, 2048, 44100);
		ALenum e = alGetError();
		if (e != AL_NO_ERROR)
			return;
		alGenSources(1, &Source);
		alSourcei(Source, AL_BUFFER, Buffer);
	}

}