#pragma once


namespace PlayerCore
{
	class VideoFrame;
	class VideoRender
	{
	public:
		VideoRender();
		virtual ~VideoRender();
		virtual void init() {}

		void updateFrame(VideoFrame*& frame);
		virtual void render() = 0;
		VideoFrame* frame_;
	protected:
		
	private:
		VideoRender(const VideoRender&) = delete;
		VideoRender& operator=(const VideoRender&) = delete;
	};
}


