#include "stdafx.h"
#include "StringPiece.h"

StringPiece::StringPiece(const string& other)
	:string(other)
{

}

StringPiece::StringPiece(const char* str)
	: string(str)
{

}

void StringPiece::Split(const string& delimiter, std::vector<StringPiece>& out)
{
	out.clear();
	for (size_type begin_index = 0, end_index = 0; end_index != StringPiece::npos;
		begin_index = end_index + delimiter.size())
	{
		end_index = find(delimiter, begin_index);
		StringPiece term = end_index == StringPiece::npos
			? substr(begin_index)
			: substr(begin_index, end_index - begin_index);

		out.push_back(term);
	}
}

bool StringPiece::BeginWith(const string& str) const
{
	size_t _sizeOther = str.size();
	size_t _sizeThis = size();
	if (_sizeThis < _sizeOther)
	{
		return false;
	}

	return 0 == memcmp(c_str(), str.c_str(), _sizeOther);
}

bool StringPiece::EndWith(const string& str) const
{
	size_t _sizeOther = str.size();
	size_t _sizeThis = size();
	if (_sizeThis < _sizeOther)
	{
		return false;
	}

	return 0 == strcmp(c_str() + (_sizeThis - _sizeOther), str.c_str());
}

