#ifndef STACKLIST_H_
#define STACKLIST_H_

#include <memory>

template <typename T>
class stackNode
{
public:
	T m_data;
	stackNode* m_pre_node;
};

template<typename T, typename Alloc>
class stackList
{
public:
	typedef stackNode<T> node;
	typedef typename Alloc::template rebind<node>::other allocator;

	stackList();
	~stackList();

	bool empty();
	void clear();
	void push(T element);
	T pop();	

private:
	allocator m_allocator;
	node* m_head_node;
};

template <typename T, typename Alloc>
stackList<T, Alloc>::stackList()
{
	m_head_node = nullptr;
}

template <typename T, typename Alloc>
stackList<T, Alloc>::~stackList()
{
	clear();
}

template <typename T, typename Alloc>
void stackList<T, Alloc>::push(T element)
{
	node* new_node = m_allocator.allocate(1);
	m_allocator.construct(new_node, node());
	new_node->data = element;
	new_node->pre_node = m_head_node;
	m_head_node = new_node;
}

template <typename T, typename Alloc>
bool stackList<T, Alloc>::empty()
{
	return (m_head_node == nullptr);
}

template <typename T, typename Alloc>
T stackList<T, Alloc>::pop()
{
	T result = m_head_node->data;
	node* temp = m_head_node->pre_node;
	m_allocator.destroy(m_head_node);
	m_allocator.deallocate(m_head_node, 1);
	m_head_node = temp;
	return result;
}

template <typename T, typename Alloc>
void stackList<T, Alloc>::clear()
{
	node* current_node = m_head_node;
	while (current_node)
	{
		node* temp = current_node->pre_node;
		m_allocator.destroy(current_node);
		m_allocator.deallocate(current_node, 1);
		current_node = temp;
	}
	m_head_node = nullptr;
}

#endif