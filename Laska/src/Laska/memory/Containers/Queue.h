#pragma once

#include <cassert>
#include <stdint.h>

namespace Laska
{
	template<typename T>
	class Queue
	{
	private:
		T* m_first;
		T* m_last;
		T* m_end;

	public:
		Queue(const int capacity = 2)
		{
			m_first = new T[capacity];
		}

		~Queue()
		{
			delete[] m_data;
		}

		void Enqueue(T& value)
		{

		}
	};
}
