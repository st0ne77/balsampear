#pragma once
#include "Base/StringPiece.h"
using balsampear::StringPiece;
class Shader
{
public:
	Shader(const StringPiece& vertexShaderPath, const StringPiece& fragmentShaderPath);
	~Shader();
	void use();
	void setFloat(const StringPiece& name, float value) const;
	void setInt(const StringPiece& name, int value) const;

private:
	unsigned int ID_;
};

