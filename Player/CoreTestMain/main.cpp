// CoreTestMain.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <gtest/gtest.h>

int main()
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

