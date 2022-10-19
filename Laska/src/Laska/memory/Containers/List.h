#pragma once

namespace Laska
{
	template <typename T>
	class List
	{
	private:
		T* m_first;
		T* m_last;
		T* m_end;

	public:
		List(const int capacity = 2)
		{
			m_first = new T[capacity];
			m_last = m_first;
			m_end = m_first + capacity;
		}

		~List()
		{
			delete[] m_first;
		}

		uint64_t Count() const
		{
			return static_cast<uint64_t>(m_last - m_first);
		}

		uint64_t Capacity() const
		{
			return static_cast<uint64_t>(m_end - m_first);
		}

		T* Data() const
		{
			return m_first;
		}

		void Clear() 
		{
			m_last = m_first;
		}

		void Add(const T& item)
		{
			if (m_last == m_end)
			{
				uint64_t capacity = static_cast<uint64_t>(m_end - m_first);

				T* old = m_first;
				m_first = new T[capacity * 2];
				memcpy(m_first, old, capacity * sizeof(T));
				m_last = m_first + capacity;
				m_end = m_first + capacity * 2;

				delete old;
			}

			*(m_last++) = item;
		}

		T& operator[](const uint64_t index)
		{
			return m_first[index];
		}
	};
}
