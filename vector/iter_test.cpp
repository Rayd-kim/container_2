#include "vector_prev.hpp"


int main()
{
	ft::vector<int>	test;

	test.push_back(1);
	test.push_back(2);
	test.push_back(3);
	test.push_back(4);

	ft::vector<int>::iterator	iter = test.begin();
	std::cout << *iter << std::endl;
	++iter;
	std::cout << *iter << std::endl;

}