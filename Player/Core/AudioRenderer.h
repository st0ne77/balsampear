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
	protected:
		AudioRenderer(const AudioRenderer&) = delete;
		AudioRenderer& operator=(const AudioRenderer&) = delete;
	};
}