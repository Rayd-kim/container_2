#include <iostream>
#include <vector>
#include "vector_test.hpp"

class test{

	public:
		int*	arr;
		int		len;
		test(){
			arr = new int[10];
			len = 0;
		}

		~test(){
			std::cout << "test destructor" << std::endl;
			// delete[]	arr;
		}


};

int	main()
{
	std::vector<test>	v1;
	ft::vector<test>	v2;

	test*	test1 = new test;
	test*	test2 = new test;
	test*	test3 = new test;


	// v1.push_back(test1);
	// v1.push_back(test2);

	v2.push_back(*test1);
	v2.push_back(*test2);
	v2.push_back(*test3);

	v2.clear();

	std::cout << v2.capacity() << std::endl;
	std::cout << v2.front().len << std::endl;

	// system("leaks a.out");
}