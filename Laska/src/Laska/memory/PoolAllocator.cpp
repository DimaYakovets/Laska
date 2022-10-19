#include "PoolAllocator.h"

namespace Laska
{
	PoolAllocator::PoolAllocator(int32_t capacity)
	{
		
		m_pool = new uint8_t[capacity];
	}

	PoolAllocator::~PoolAllocator()
	{
		delete[] m_pool;
	}


	void* PoolAllocator::Allocate()
	{
		return nullptr;
	}


	void PoolAllocator::Free(void* ptr)
	{

	}
}
