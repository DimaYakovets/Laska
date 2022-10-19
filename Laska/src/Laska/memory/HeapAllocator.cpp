#include <Laska/memory/HeapAllocator.h>

namespace Laska
{
	void* HeapAllocator::Allocate(size_t size)
	{
		return malloc(size);
	}

	void HeapAllocator::Free(void* ptr)
	{
		free(ptr);
	}
}
