#include <iostream>
#include <vector>
#include <ctime>
#include <cassert>
#include "StackList.h"
#include "MemoryPool.h"

#define ELEMS  25000000
#define TEST_TYPE int
//

int main()
{
	clock_t time_start;

	stackList<TEST_TYPE, std::allocator<TEST_TYPE> > std_test_stack_list;
	time_start = clock();
	for (int i = 0; i < ELEMS; ++i)
	{
		std_test_stack_list.push(i);
		std_test_stack_list.pop();
	}
	std::cout <<((clock() - time_start) / CLOCKS_PER_SEC) << '\n';

	stackList<TEST_TYPE, blockAllocator<TEST_TYPE> > ba_test_stack_list;
	time_start = clock();
	for (int i = 0; i < ELEMS; ++i)
	{
		ba_test_stack_list.push(i);
		ba_test_stack_list.pop();
	}
	std::cout << ((clock() - time_start) / CLOCKS_PER_SEC)<< '\n';

	system("pause");
}