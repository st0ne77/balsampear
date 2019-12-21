#pragma once

using Byte = unsigned char;
namespace balsampear
{
	class VideoRenderer
	{
	public:
		VideoRenderer();
		virtual ~VideoRenderer();

	private:
		VideoRenderer(const VideoRenderer&) = delete;
		VideoRenderer& operator =(const VideoRenderer&) = delete;
	};
}


