#ifndef MEMORYPOOL_H
#define MEMORYPOOL_H

template<typename T>
class memoryPool
{
private:
	typedef char* data_ptr;
	typedef 

public:
	memoryPool();
	~memoryPool();

	T* allocate();
	void deallocate();

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

}

template<typename T>
memoryPool::~memoryPool()
{
}

template<typename T>
T* memoryPool::allocate()
{

}

template<typename T>
void memoryPool::deallocate()
{

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
