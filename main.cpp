#include <iostream>
#include <vector>
#include <ctime>
#include "StackList.h"

#define  ELEMS  25000000

int main()
{
	clock_t time_start;
	stackList<int, std::allocator<int> > test_stack_list;
	time_start = clock();
	for (int i = 0; i < ELEMS; ++i)
	{
		test_stack_list.push(i);
		test_stack_list.pop();
	}
	std::cout << ((clock() - time_start) / CLOCKS_PER_SEC)<< '\n';

	system("pause");
}