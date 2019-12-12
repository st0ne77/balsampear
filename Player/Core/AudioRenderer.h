#pragma once

namespace balsampear
{
	class AudioRenderer
	{
	public:
		AudioRenderer();
		virtual ~AudioRenderer();

		void init();

		void play();

		void update(void* data);

		size_t queuedFrameNum();
		void unqueue();
	protected:
		AudioRenderer(const AudioRenderer&) = delete;
		AudioRenderer& operator=(const AudioRenderer&) = delete;
	};
}