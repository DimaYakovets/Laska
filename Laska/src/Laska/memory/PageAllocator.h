#pragma once

#include <stack>
#include "Allocator.h"

namespace Laska
{
	using byte = uint8_t;

	struct MemoryPage
	{
		byte* m_ptr;
		byte* m_pen;
		byte* m_end;

		MemoryPage() = default;
		MemoryPage(MemoryPage&) = default;
		MemoryPage(uint32_t pageSize)
		{
			m_ptr = new byte[pageSize];
			m_pen = m_ptr;
			m_end = m_ptr + pageSize;

			memset(m_ptr, 0x00, pageSize);
		}

		~MemoryPage()
		{
			delete m_ptr;
		}

		MemoryPage& operator=(MemoryPage& o)
		{
			this->m_ptr = o.m_ptr;
			this->m_pen = o.m_pen;
			this->m_end = o.m_end;

			return *this;
		}

		MemoryPage& operator=(MemoryPage&& o) noexcept
		{
			this->m_ptr = o.m_ptr;
			this->m_pen = o.m_pen;
			this->m_end = o.m_end;
			o.m_ptr = nullptr;

			return *this;
		}
	};

	class PageAllocator : public Allocator
	{
	private:
		static const int KB = 1024;
		static const int MB = 1024 * 1024;

		size_t m_pageSize;
		size_t m_cellSize;
		size_t m_cellsPerPage;
		uint32_t m_pagesCount;
		MemoryPage* m_pages;

		std::stack<byte*> m_free;

	public:
		PageAllocator() = default;
		PageAllocator(const PageAllocator&) = default;
		PageAllocator(size_t cellSize);
		~PageAllocator();

		void* Allocate(size_t size) override;
		void Free(void* ptr) override;

		MemoryPage* GetPages();

		PageAllocator& operator= (PageAllocator&& o) noexcept
		{
			this->m_cellSize = o.m_cellSize;
			this->m_pagesCount = o.m_pagesCount;
			this->m_free = o.m_free;
			this->m_pages = o.m_pages;
			this->m_pageSize = o.m_pageSize;
			o.m_pages = nullptr;

			return *this;
		}
	};
}
