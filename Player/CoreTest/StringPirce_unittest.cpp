#include "pch.h"
#include "Base/StringPiece.h"
#include "AVParser.h"

using PlayerCore::StringPiece;
using namespace std;

TEST(StirngPieceTest, HandleString)
{
	StringPiece str = "123456789";
	vector<StringPiece> result0 =  str.Split("46");
	ASSERT_EQ(3, result0.size());
	ASSERT_STREQ("123", result0[0].c_str());
	ASSERT_STREQ("5", result0[1].c_str());
	ASSERT_STREQ("789", result0[2].c_str());

	vector<StringPiece> result1 = str.SplitUsingSubstr("46");
	ASSERT_EQ(1, result1.size());
	ASSERT_STREQ("123456789", result1[0].c_str());

	vector<StringPiece> result2 = str.SplitUsingSubstr("45");
	ASSERT_EQ(2, result2.size());
	ASSERT_STREQ("123", result2[0].c_str());
	ASSERT_STREQ("6789", result2[1].c_str());
}

TEST(StirngPieceTest, HandleStdString)
{
	string StdString_ = "123";
	StringPiece StringP = StdString_;
	ASSERT_STREQ(StdString_.c_str(), StringP.c_str());
	string StdString_1 = StringP;
	ASSERT_STREQ(StdString_1.c_str(), StdString_.c_str());
}