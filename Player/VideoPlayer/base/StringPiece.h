#pragma once
#include <string>
#include <vector>
using string = std::string;
class StringPiece :public string
{
public:
	StringPiece(const string& other);
	StringPiece(const char* str);
	void Split(const string& delimiter, std::vector<StringPiece>& out);
	bool BeginWith(const string& str) const;
	bool EndWith(const string& str) const;
};