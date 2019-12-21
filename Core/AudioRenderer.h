#pragma once
#include <map>

using uint64 = unsigned long long;
namespace balsampear
{
	class AudioRenderer
	{
	public:
		AudioRenderer();
		virtual ~AudioRenderer();

		void init();

		void play();
		void pause();
		void stop();

		void queue(void* data, uint64 timestamp_msec);
		uint64 unqueue();
		bool playing();

		int QueueSize();
		
	protected:
		AudioRenderer(const AudioRenderer&) = delete;
		AudioRenderer& operator=(const AudioRenderer&) = delete;

		std::map<int, uint64> buffermap_;
	};
}