#include <Laska/memory/PageAllocator.h>

namespace Laska
{
	PageAllocator::PageAllocator(size_t cellSize)
		: m_pageSize((4 * KB / cellSize + 1) * cellSize), 
		m_cellSize(cellSize), 
		m_pagesCount(1), 
		m_free(),
		m_cellsPerPage(m_pageSize / m_cellSize)
	{
		m_pages = new MemoryPage[m_pagesCount];

		for (size_t i = 0; i < m_pagesCount; i++)
		{
			new (m_pages + i) MemoryPage(m_pageSize);
		}
	}

	PageAllocator::~PageAllocator()
	{
		delete[] m_pages;
	}

	void* PageAllocator::Allocate(size_t size)
	{
		if (m_free.size() > 0)
		{
			byte* ptr = m_free.top();
			m_free.pop();

			return ptr;
		}

		MemoryPage& page = m_pages[m_pagesCount - 1];

		if ((page.m_end - page.m_pen) >= m_cellSize)
		{
			byte* ptr = page.m_pen;
			page.m_pen += m_cellSize;

			return ptr;
		}
		else
		{
			int oldCount = m_pagesCount;
			MemoryPage* old = m_pages;

			m_pages = new MemoryPage[++m_pagesCount];
			memcpy(m_pages, old, sizeof(MemoryPage) * (oldCount));

			delete old;

			m_pages[oldCount] = MemoryPage(m_pageSize);
			page = m_pages[oldCount];

			byte* ptr = page.m_pen;
			page.m_pen += m_cellSize;

			return ptr;
		}
	}

	void PageAllocator::Free(void* ptr)
	{
		m_free.push((byte*)ptr);
	}

	MemoryPage* PageAllocator::GetPages()
	{
		return m_pages;
	}
}
