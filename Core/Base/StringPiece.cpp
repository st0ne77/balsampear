#include "StringPiece.h"

namespace balsampear
{
	StringPiece::StringPiece()
		:string()
	{

	}

	StringPiece::StringPiece(const string& other)
		:string(other)
	{

	}

	StringPiece::StringPiece(const char* str)
		: string(str)
	{

	}

	

	std::vector<StringPiece> StringPiece::Split(const string& separators, bool ignoreWhiteSpace /*= false*/)
	{
		std::vector<StringPiece> result;
		if (empty())
		{
			return result;
		}	

		size_t start = 0;
		while (start != string::npos) 
		{
			size_t end = find_first_of(separators, start);

			StringPiece piece;
			if (end == string::npos)
			{
				piece = substr(start);
				start = string::npos;
			}
			else 
			{
				piece = substr(start, end - start);
				start = end + 1;
			}

			if (ignoreWhiteSpace && piece.empty())
			{
				continue;
			}

			result.push_back(piece);
		}
		return result;
	}

	std::vector<StringPiece> StringPiece::SplitUsingSubstr(const string& delimiter, bool ignoreWhiteSpace /*= false*/)
	{
		std::vector<StringPiece> result;
		for (size_type begin_index = 0, end_index = 0; end_index != StringPiece::npos;
			begin_index = end_index + delimiter.size())
		{
			end_index = find(delimiter, begin_index);
			StringPiece term = end_index == StringPiece::npos
				? substr(begin_index)
				: substr(begin_index, end_index - begin_index);

			if (ignoreWhiteSpace && term.empty())
			{
				continue;
			}

			result.push_back(term);
		}
		return result;
	}

}