#include "AudioRenderer.h"
#include "AL/al.h"
#include "AL/alc.h"
#include "AL/alext.h"
#include <corecrt_memory.h>
#include <assert.h>
namespace balsampear
{
	ALCcontext* m_Context = nullptr;
	AudioRenderer::AudioRenderer()
	{

	}

	AudioRenderer::~AudioRenderer()
	{
		ALCdevice * device = alcGetContextsDevice(m_Context);
		alcMakeContextCurrent(NULL);
		alcDestroyContext(m_Context);
		alcCloseDevice(device);
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
			m_Context = alcCreateContext(m_Devicde, nullptr);

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
		int state;
		alGetSourcei(Source, AL_SOURCE_STATE, &state);
		if (state == AL_STOPPED || state == AL_INITIAL || state == AL_PAUSED)
		{
			alSourcePlay(Source);
		}
	}

	void AudioRenderer::pause()
	{
		alSourcePause(Source);
		ALint processed = 0;		
	}


	void AudioRenderer::stop()
	{
		alSourceStop(Source);
		int size = 0;
		alGetSourcei(Source, AL_BUFFERS_PROCESSED, &size);
	}

	using Byte = unsigned char;
	void AudioRenderer::queue(void* data, uint64 timestamp_msec)
	{
		
		alGenBuffers(1, &Buffer);
		if (alGetError() != AL_NO_ERROR)
			return ;

		alBufferData(Buffer, AL_FORMAT_STEREO8, data, 2048, 44100);
		ALenum e = alGetError();
		assert(e == AL_NO_ERROR);
		alSourceQueueBuffers(Source, 1, &Buffer);
		buffermap_.insert(std::make_pair(Buffer, timestamp_msec));
		return ;
	}

	bool AudioRenderer::playing()
	{
		int state;
		alGetSourcei(Source, AL_SOURCE_STATE, &state);
		if (state != AL_PLAYING)
		{
			int i = 0;
		}
		if (state == AL_PLAYING)
		{
			int i = 0;
		}
		return state == AL_PLAYING;
	}


	int AudioRenderer::QueueSize()
	{
		int size = 0;
		alGetSourcei(Source, AL_BUFFERS_PROCESSED, &size);
		return size;
	}

	uint64 AudioRenderer::unqueue()
	{
		uint64 timestamp = 0;
		ALint processed = 0;
		alGetSourcei(Source, AL_BUFFERS_PROCESSED, &processed);
		if (processed > 0)
		{
			ALuint *bufferID = new ALuint[processed];
			alSourceUnqueueBuffers(Source, processed, bufferID);
			alDeleteBuffers(processed, bufferID);
			std::map<int, uint64>::iterator it = buffermap_.find(bufferID[processed - 1]);
			if (it != buffermap_.end())
			{
				timestamp = it->second;
				buffermap_.erase(it);
			}
			delete[] bufferID;
		}
		return timestamp;
	}

}