#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

#define MP_DELETE(p)	if (p) {delete p; p = nullptr;}
#define BLOCKSIZE 4096

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

	assert(BLOCKSIZE >= 2*sizeof(slot), "BLOCKSIZE is too small");

public:
	memoryPool();
	~memoryPool();

	T* allocate();
	void deallocate(T* ptr);

	void construct();
	void destroy();

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
T* memoryPool::allocate()
{

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

template<typename T>
void memoryPool::construct()
{

}

template<typename T>
void memoryPool::destroy()
{

}

#endif
