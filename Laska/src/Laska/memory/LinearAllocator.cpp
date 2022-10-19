#include "LinearAllocator.h"

namespace Laska
{
	LinearAllocator::LinearAllocator(void* buffer, size_t size)
		: m_buffer(buffer), m_pointer(buffer), m_end((void*)((uint8_t*)buffer + size))
	{

	}

	LinearAllocator::~LinearAllocator()
	{
		
	}

	void* LinearAllocator::Allocate(size_t size)
	{
		if ((uint8_t*)m_pointer + size >= (uint8_t*)m_end)
		{
			return nullptr;
		}

		void* ptr = m_pointer;

		m_pointer = (uint8_t*)(m_pointer) + size;

		return ptr;
	}

	void LinearAllocator::Reset()
	{
		m_pointer = m_buffer;
	}
}
