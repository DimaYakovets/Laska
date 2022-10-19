#pragma once

#include <stdint.h>
#include "Allocator.h"

namespace Laska
{
	class PoolAllocator
	{
	private:
		struct Chunk
		{
			Chunk* pNext;
		};

	private:
		uint8_t* m_pool;
		uint32_t m_pointer;

	public:
		PoolAllocator(int32_t cellsize);
		~PoolAllocator();

		void* Allocate();
		void Free(void* ptr);
	};
}
