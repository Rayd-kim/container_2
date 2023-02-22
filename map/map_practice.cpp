#include <iostream>
#include "map.hpp"
#include <map>

int	main()
{
	ft::map<int, std::string>	m;
	

	m[42] = "lol";

	m[50] = "mdr";
	m[25] = "funny";

	m[46] = "bunny";
	m[21] = "fizz";
	m[30] = "buzz";
	m[55] = "fuzzy";

	m[18] = "bee";
	m[23] = "coconut";
	m[28] = "diary";
	m[35] = "fiesta";
	m[44] = "hello";
	m[48] = "world";
	m[53] = "this is a test";
	m[80] = "hey";

	m[12] = "no";
	m[20] = "idea";
	m[22] = "123";
	m[24] = "345";
	m[27] = "27";
	m[29] = "29";
	m[33] = "33";
	m[38] = "38";

	m[43] = "1";
	m[45] = "2";
	m[47] = "3";
	m[49] = "4";
	m[51] = "5";
	m[54] = "6";
	m[60] = "7";
	m[90] = "8";
	

	ft::map<int, std::string>::iterator	iter = m.begin();	


	// for (; iter != m.end(); iter++)
	// 	std::cout << "key : " << iter->first << " value :" << iter->second << std::endl;
	
	printf("---After erase----\n");
	// printf("erase 25\n");
	m.erase(25);
	// printf("erase 55\n");
	m.erase(55);
	// printf("erase 24\n");
	m.erase(24);
	// printf("erase 54\n");
	// m.erase(54);
	// printf("erase 22\n");
	// m.erase(22);
	// printf("erase 51\n");
	// m.erase(51);
	// printf("erase 21\n");
	// m.erase(21);
	// printf("erase 53\n");
	// m.erase(53);
	// printf("erase 20\n");
	// m.erase(20);
	// printf("erase 23\n");
	// m.erase(23);
	// printf("erase 42\n");
	// m.erase(42);
	// printf("erase 38\n");
	// m.erase(38);
	// printf("erase 35\n");
	// m.erase(35);
	// printf("erase 33\n");
	// m.erase(33);

	// std::cout << m._tree.root <<std::endl;

	iter = m.begin();
	for (; iter != m.end(); iter++)
	{
		std::cout << "key : " << iter->first << " value :" << iter->second << std::endl;
		
		std::cout << iter.base()->value.first << std::endl;
		std::cout << iter.base()->left->value.first << std::endl;
		std::cout << iter.base()->right->value.first << std::endl;
		if (iter.base()->right->parent != NULL)
			std::cout << iter.base()->right->parent->value.first << std::endl;
		if (iter.base()->left->parent != NULL)
			std::cout << iter.base()->left->parent->value.first << std::endl;
		
		std::cout << std::endl;
	}
}