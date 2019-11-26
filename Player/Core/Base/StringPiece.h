#pragma once
#include <string>
#include <vector>
using string = std::string;
namespace PlayerCore
{
	class StringPiece :public string
	{
	public:
		StringPiece();
		StringPiece(const string& other);
		StringPiece(const char* str);
		std::vector<StringPiece> Split(const string& separators, bool ignoreWhiteSpace = false);
		std::vector<StringPiece> SplitUsingSubstr(const string& delimiter, bool ignoreWhiteSpace = false);
	};
}
