#include <memory>

template <typename T>
class stackNode
{
private:
	T data;
	stackNode* pre_node;
};

template<typename T, typename Alloc = std::allocator<T>>
class stackAlloc
{
public:
	typedef stackNode node;
	typedef Alloc::rebind<node>::other allocator;

	stackAlloc();
	~stackAlloc();

	bool empty();
	void clear();
	void push<T element>;
	T pop();
	T getTop();

private:
	allocator allocator_;

};