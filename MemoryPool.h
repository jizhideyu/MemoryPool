#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#define MP_DELETE(p)	if (p) {delete p; p = nullptr;}
#define BLOCK_SIZE 4096

template<typename T>
class memoryPool
{
private:
	union slot
	{
		slot* next;
		T element;		
	};
	typedef char* dataPtr;
	typedef slot* slotPtr;

	slotPtr m_current_block;
	slotPtr m_current_slot;
	slotPtr m_last_slot;
	slotPtr m_free_slots;

	assert(BLOCK_SIZE >= 2 * sizeof(slot), "BLOCKSIZE is too small");

public:
	memoryPool();
	~memoryPool();

	T* allocate(size_t n = 1);
	void deallocate(T* ptr);

	template<typename U, typename... Args>
	void construct(U* p, Args... args);
	template<typename U>
	void destroy(U* p);

	template<typename U>
	class rebind
	{
	public:
		typedef	memoryPool<U> other;
	};
};

template<typename T>
memoryPool::memoryPool()
{
	m_current_block = nullptr;
	m_current_slot = nullptr;
	m_last_slot = nullptr;
	m_free_slots = nullptr;
}

template<typename T>
memoryPool::~memoryPool()
{
	slotPtr cur_ptr = m_current_block;
	while (cur_ptr != nullptr)
	{
		slotPtr pre_ptr = cur_ptr->next;
		MP_DELETE(cur_ptr);
		cur_ptr = pre_ptr;
	}
}

template<typename T>
T* memoryPool::allocate(size_t n = 1)
{
	if (m_free_slots)
	{
		T* result = reinterpret_cast<T*>(m_free_slots);
		m_free_slots = m_free_slots.next;
		return result;
	}
	else
	{
		if (m_current_slot >= m_last_slot)
		{
			dataPtr newBlock = reinterpret_cast<dataPtr>(operator new(BLOCK_SIZE));
			reinterpret_cast<slotPtr>(newBlock)->next = m_current_block;
			m_current_block = reinterpret_cast<slotPtr>(newBlock);

			dataPtr body = newBlock + sizeof(slotPtr);
			UINT_PTR result = reinterpret_cast<UINT_PTR>(body);
			size_t body_padding = result - (result / alignof(slot) * alignof(slot));
			m_current_slot = reinterpret_cast<slotPtr>(body + body_padding);
			m_last_slot = reinterpret_cast<slotPtr>(newBlock + BLOCK_SIZE - sizeof(slot));
		}
		return reinterpret_cast<T*>(m_current_slot++);
	}
}

template<typename T>
void memoryPool::deallocate(T* ptr)
{
	if (ptr != nullptr)
	{
		reinterpret_cast<slotPtr>(ptr)->next = m_free_slots;
		m_free_slots = reinterpret_cast<slotPtr>(ptr);
	}
}

template<typename U, typename... Args>
void memoryPool::construct(U* p, Args... args)
{
	new (p) U(std::forward<Args>(args)...);
}

template<typename U>
void memoryPool::destroy(U* p)
{
	p->~U();
}

#endif
