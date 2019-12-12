#include "pch.h"
#include "Base/MemoryPool.h"



TEST(MemoryPoolTest, handlePool)
{
	balsampear::MemoryPool<char> pool;
	pool.allocate<123>(1);
}