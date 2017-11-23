#ifndef STACKLIST_H_
#define STACKLIST_H_

#include <memory>

template <typename T>
class stackNode
{
private:
	T data;
	stackNode* pre_node;
};

template<typename T, typename Alloc>
class stackList
{
public:
	typedef stackNode node;
	typedef typename Alloc::template rebind<node>::other allocator;

	stackList();
	~stackList();

	bool empty();
	void clear();
	void push(T element);
	T pop();
	T getTop();

private:
	allocator allocator_;
	node* head_node_;
};

#endif