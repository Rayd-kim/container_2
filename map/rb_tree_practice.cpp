#include "RB_tree_compare_version.hpp"

int	main(void)
{
	RB_tree<int, std::string>	rb_tree;
	std::map<int, std::string>	map1;

	map1.insert(make_pair(1, (std::string)"1"));

	rb_tree.insert_node(make_pair(1, (std::string)"1"));
	rb_tree.insert_node(make_pair(2, (std::string)"2"));
	rb_tree.insert_node(make_pair(5, (std::string)"5"));
	rb_tree.insert_node(make_pair(4, (std::string)"4"));
	rb_tree.insert_node(make_pair(3, (std::string)"3"));
	rb_tree.insert_node(make_pair(6, (std::string)"6"));
	rb_tree.insert_node(make_pair(8, (std::string)"8"));
	rb_tree.insert_node(make_pair(7, (std::string)"7"));
	rb_tree.insert_node(make_pair(10, (std::string)"10"));
	rb_tree.insert_node(make_pair(11, (std::string)"11"));
	rb_tree.insert_node(make_pair(9, (std::string)"9"));

	rb_tree.print_tree();
	printf("-----------\n");

	RB_tree<int, std::string>::node_pointer	iter = rb_tree._end;
	while (iter != rb_tree._begin)
	{
		iter = rb_tree.prev_node(iter);
		std::cout << iter->value.first << std::endl;
	}

	// while(iter != rb_tree.nil)
	// {
	// 	std::cout << iter->value.first << std::endl;
	// 	rb_tree.plus_node(iter);
	// }


	// std::cout << iter->value.first << std::endl;
	// iter = rb_tree.next_node(iter);
	// std::cout << iter->value.first << std::endl;
	// iter = rb_tree.next_node(iter);
	// std::cout << iter->value.first << std::endl;
	// iter = rb_tree.next_node(iter);
	// std::cout << iter->value.first << std::endl;

	

	// system("leaks a.out");
	
}