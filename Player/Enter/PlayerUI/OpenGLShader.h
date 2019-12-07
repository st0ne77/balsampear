#pragma once
#include "Base/StringPiece.h"
namespace PlayerCore
{
	//use after init OpenGL
	class OpenGLShader
	{
	public:
		OpenGLShader(const StringPiece& vert, const StringPiece& frag);
		~OpenGLShader();

		void use();
		void setFloat(const StringPiece& name, float value) const;
		void setInt(const StringPiece& name, int value) const;
	protected:
		OpenGLShader(const OpenGLShader&) = delete;
		OpenGLShader& operator =(const OpenGLShader&) = delete;
	private:
		unsigned int id_;
	};
}