#include "stackList.h"

using namespace std;

template <typename T, typename Alloc>
stackList<T, Alloc>::stackList()
{
	head_node_ = nullptr;
}

template <typename T, typename Alloc>
stackList<T, Alloc>::~stackList()
{
	clear();
}

template <typename T, typename Alloc>
void stackList<T, Alloc>::push(T element)
{
	node* new_node = allocator_.allocate(1);
	allocator_.construct(new_node, node());
	new_node->data = element;
	new_node->pre_node = head_node_;
	head_node_ = new_node;
}

template <typename T, typename Alloc>
bool stackList<T, Alloc>::empty()
{
	return (head_node_ == nullptr);
}

template <typename T, typename Alloc>
T stackList<T, Alloc>::pop()
{ 
	T result = head_node_->data;
	node* temp = head_node_->pre_node;
	allocator_.destroy(head_node_);
	allocator_.deallocate(head_node_, 1);
	head_node_ = temp;
}

template <typename T, typename Alloc>
void stackList<T, Alloc>::clear()
{
	node* current_node = head_node_;
	while (current_node)
	{
		node* temp = current_node->pre_node;
		allocator_.destroy(current_node);
		allocator_.deallocate(current_node, 1);
		current_node = temp;
	}
	head_node_ = nullptr;
}