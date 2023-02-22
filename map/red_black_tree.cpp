#include <iostream>
#include <stdexcept>
#include <map>

#define RED 			1
#define BLACK			2

template <typename _pair>
struct Node {
	public:
	_pair	value;
	Node	*parent;
	Node	*left;
	Node	*right;
	int		red_black;

	Node(_pair pair) : value(pair), parent(NULL), left(NULL), right(NULL), red_black(RED) //일반 insert때의 노드 생성
	{}

	Node() : parent(NULL), left(NULL), right(NULL), red_black(BLACK)//leaf node(nil_node) 생성
	{}
	
};

template<typename Key, typename Value, typename Compare = std::less<Key>, 
typename Allocator = std::allocator<std::pair<const Key, Value> > >
class RB_tree{
	private:
		size_t	_size;

	public:
	typedef	Key									key_type;
	typedef	Value								mapped_type;
	typedef	std::pair<const Key, Value>			value_type;
	typedef	Allocator							Alloc;
	typedef	value_type&							reference;
	typedef	typename Allocator::size_type		size_type;
	typedef	Node<value_type>					node_type;
	typedef	node_type*							node_pointer;
	// typedef	typename Alloc::template rebind<Node>::other	Alnode;

	Node<value_type>	*root;
	Node<value_type>	*insert_temp;
	Node<value_type>	*nil;

	Node<value_type>	*_begin;
	Node<value_type>	*_end;

	RB_tree() : root(NULL), insert_temp(NULL)
	{
		nil = new Node<value_type>;
		_begin = nil;
		_end = nil;
		_size = 0;
	}

	Node<value_type>* create_new_node(value_type pair)
	{
		Node<value_type>	*ret = new Node<value_type>(pair);
		ret->left = nil;
		ret->right = nil;
		if (_begin == nil)
			_begin = ret;
		else if (_begin->value.first > pair.first)
			_begin = ret;
		return (ret);
	}

	void	insert_node(value_type pair)
	{
		if (root == NULL)
		{
			root = create_new_node(pair);
			root->red_black = BLACK;
			insert_temp = root;
			_size++;
		}
		else if (pair.first < insert_temp->value.first)
		{
			if (insert_temp->left == nil)
			{
				insert_temp->left = create_new_node(pair);
				insert_temp->left->parent = insert_temp;
				red_black_check(insert_temp->left);
				insert_temp = root;
				_size++;
			}
			else
			{
				insert_temp = insert_temp->left;
				insert_node(pair);
			}
		}
		else if (pair.first > insert_temp->value.first)
		{
			if (insert_temp->right == nil)
			{
				insert_temp->right = create_new_node(pair);
				insert_temp->right->parent = insert_temp;
				red_black_check(insert_temp->right);
				insert_temp = root;
				_size++;
			}
			else
			{
				insert_temp = insert_temp->right;
				insert_node(pair);
			}
		}
		else
			insert_temp = root;
	}

	void	inored_node(Node<value_type> *root)
	{
		if (root == NULL || root == nil)
			return ;
		inored_node(root->left);
		// if (root->parent != NULL)
		// 	std::cout << "key: " << root->value.first << "  parent key: " << root->parent->value.first << "  1red_2black " << root->red_black << std::endl;
		// else
		std::cout << "key: " << root->value.first << std::endl;
		inored_node(root->right);
	}

	void	print_tree()
	{
		inored_node(root);
	}

	void	left_rotate(Node<value_type> *node)
	{
		Node<value_type>	*temp_parent;
		Node<value_type>	*node_left;

		node_left = node->left;  //node->left save
		temp_parent = node->parent->parent; //parent->parent save

		node->parent->right = node_left; //현재 노드의 부모노드의 오른쪽 노드를 현재 노드의 왼쪽으로 변경 
		node_left->parent = node->parent;

		node->left = node->parent; // 현재 노드의 왼쪽이 부모노드를 가리키도록 변경
		node->left->parent = node; // 원래 부모노드가 현재노드의 왼쪽으로 변경되었으므로, 원래 부모노드의 부모노드를 현재노드로 변경
		node->parent = temp_parent; // 현재노드의 부모노드를 원래의 부모의 부모노드로 변경


		if (node->parent == NULL) //root node일 때
			root = node;
		else
		{
			if (node->parent->right == node->left)
				node->parent->right = node;
			else
				node->parent->left = node;
		}
	}

	void	right_rotate(Node<value_type> *node)
	{
		Node<value_type>	*temp_parent;
		Node<value_type>	*node_right;


		node_right = node->right; // 현재노드의 오른쪽 저장
		temp_parent = node->parent->parent; // 현재부모노드의 부모노드(조부모노드)를 저장

		node->parent->left = node_right; // 부모노드의 왼쪽노드(현재노드임)를 현재노드의 오른쪽으로 변경
		node_right->parent = node->parent;

		node->right = node->parent; // 현재 노드의 오른쪽이 부모노드를 가리키도록 변경
		node->right->parent = node;
		node->parent = temp_parent;


		if (node->parent == NULL)
			root = node;
		else
		{
			if (node->parent->right == node->right) //parent의 좌우 노드 재설정
				node->parent->right = node;
			else
				node->parent->left = node;
		}
	}

	void	red_black_check(Node<value_type> *node)
	{
		if (node->parent == NULL) //node is root
		{
			node->red_black = BLACK;
			return ;
		}
		else if (node->parent->red_black == BLACK) // 부모가 black 이면 새로 붙여진게 red여도 ok
			return ;
		else
		{
			if (node->parent == node->parent->parent->left) //현재노드가 부모의 왼쪽기준일 때
			{
				Node<value_type>	*node_parent = node->parent;
				Node<value_type>	*node_grand_parent = node->parent->parent;

				if (node_parent->red_black == RED && node_grand_parent->right->red_black == RED)// 부모, 자식, 삼촌노드도 red 일 때.
				{
					node_parent->red_black = BLACK;
					node_grand_parent->right->red_black = BLACK;
					node_grand_parent->red_black = RED;
					red_black_check(node_grand_parent);
				}
				else if (node_grand_parent->right->red_black == BLACK && node == node_parent->right) //삼촌노드가 블랙이고, 자식이 부모의 오른쪽일때
				{
					left_rotate(node_parent);
					red_black_check(node->left);
				}
				else
				{
					node_parent->red_black = BLACK;
					node_grand_parent->red_black = RED;
					right_rotate(node_parent);
				}

			}
			else //현재 노드가 부모의 오른쪽기준일 때
			{
				Node<value_type>	*node_parent = node->parent;
				Node<value_type>	*node_grand_parent = node->parent->parent;

				if (node_parent->red_black == RED && node_grand_parent->left->red_black == RED)// 부모, 자식, 삼촌노드도 red 일 때.
				{
					node_parent->red_black = BLACK;
					node_grand_parent->left->red_black = BLACK;
					node_grand_parent->red_black = RED;
					red_black_check(node_grand_parent);
				}
				else if (node_grand_parent->left->red_black == BLACK && node == node_parent->left) //삼촌노드가 블랙이고, 자식이 부모의 오른쪽일때
				{
					right_rotate(node_parent);
					red_black_check(node->right);
				}
				else
				{
					node_parent->red_black = BLACK;
					node_grand_parent->red_black = RED;
					left_rotate(node_parent);
				}
			}	
		}
	}

	node_pointer	search_key(const Key& key)
	{
		node_pointer	ret = root;

		while (ret != nil && ret != NULL)
		{
			if (ret->value.first > key)
				ret = ret->left;
			else if (ret->value.first < key)
				ret = ret->right;
			else
				return (ret);
		}
		return (nil);
	}

	node_pointer	search_successor(node_pointer node)
	{
		node_pointer	successor;

		while (node != nil && node != NULL)
		{
			successor = node;
			node = node->left;
		}
		return successor;
	}

	void	transplant(node_pointer before, node_pointer after)
	{
		if (before->parent == NULL)
			root = after;
		else if (before == before->parent->left)
			before->parent->left = after;
		else
			before->parent->right = after;
		
		after->parent = before->parent;
	}

	void	delete_node(const Key& key)
	{
		node_pointer	node = search_key(key);

		if (node != nil)
		{
			node_pointer			del = node;
			node_pointer			extra_b; //extra black을 갖게 될 node = 삭제되는 노드의 자식.
			int	del_origin_color	= node->red_black;

			if (node->left == nil) // 오른쪽에 유효한 자식을 가질 때.
			{
				extra_b = node->right;
				transplant(node, node->right);
			}
			else if (node->right == nil) // 오른쪽에 유효한 자식을 가질 때. (!= nil로 하면 둘 다 nil일 경우가 안잡힌다.)
			{
				extra_b = node->left;
				transplant(node, node->left);
			}
			else //둘 다 black일 때, successor의 부모가 node인지 아닌지에 따라서 재조정이 조금 달라진다.
			{
				del = search_successor(node->right);
				del_origin_color = del->red_black;
				extra_b = del->right; // successor는 왼쪽노드를 절대 가질리 없다. (그러면 그 왼쪽이 successor가 되기 때문에)
				
				if (del->parent == node)
					extra_b->parent = del;
				else
				{
					transplant(del, del->right);
					del->right = node->right;
					del->right->parent = del;
				}
				transplant(node, del);
				del->left = node->left;
				del->left->parent = del;
				del->red_black = node->red_black;
			}

			//fix_up
			if (del_origin_color == BLACK)
				fixed_up_rb_tree(extra_b);
			free(node);
			_size--;
		}
		if (root == nil)
			root = NULL;
	}

	void	fixed_up_rb_tree(node_pointer extra_b)
	{
		node_pointer bro;

		while (extra_b != root && extra_b->red_black == BLACK)
		{
			if (extra_b == extra_b->parent->left) //extra_black node가 왼쪽일 떄
			{
				bro = extra_b->parent->right;
				if (bro->red_black == RED) //bro == RED일 때. case1
				{
					bro->red_black = BLACK;
					bro->parent->red_black = RED;
					left_rotate(bro);
					bro = extra_b->parent->right;
				}
				/*bro == black, bro의 child가 둘 다 black일 때. case 2
				bro의 색을 red로 바꿔 준 다음 부모에 extra_black을 넘겨서 여기서 다시 체크하도록 한다.*/
				if (bro->left->red_black == BLACK && bro->right->red_black == BLACK)
				{
					bro->red_black = RED;
					extra_b = extra_b->parent;
				}
				else //case 3, 4 case3는 재조정 후, case4의 과정으로 넘어가기 때문에 case3 인지 확인하는 과정이 포함된다.
				{
					if (bro->right->red_black == BLACK) //case 3. 왼쪽이 red이고, 오른쪽은 black일 때.
					{
						bro->left->red_black = BLACK;
						bro->red_black = RED;
						right_rotate(bro->left);
						bro = extra_b->parent->right;
					}
					// bro는 black이고, bro->right는 red인 경우. 이 때, 부모와 bro->left의 색은 상관없다.
					bro->red_black = extra_b->parent->red_black;
					extra_b->parent->red_black = BLACK;
					bro->right->red_black = BLACK;
					left_rotate(bro);
					extra_b = root;
				}
			}
			else //extra_black node가 오른쪽일 때
			{
				bro = extra_b->parent->left;
				if (bro->red_black == RED)
				{
					bro->red_black = BLACK;
					bro->parent->red_black = RED;
					right_rotate(bro);
					bro = extra_b->parent->left;
				}
				if (bro->right->red_black == BLACK && bro->left->red_black == BLACK)
				{
					bro->red_black = RED;
					extra_b = extra_b->parent;
					// std::cout << extra_b->value.first << std::endl;
					// printf("ok\n");
				}
				else
				{
					if (bro->left->red_black == BLACK) // 오른쪽이 red이고, 왼쪽은 black일 때
					{
						bro->right->red_black = BLACK;
						bro->red_black = RED;
						left_rotate(bro->right);
						bro = extra_b->parent->left;
					}
					//bro 는 black이고, bro->left는 red인 경우. 위의 경우와는 case 3, 4의 왼쪽 오른쪽이 바뀐다.
					bro->red_black= extra_b->parent->red_black;
					extra_b->parent->red_black = BLACK;
					bro->left->red_black = BLACK;
					right_rotate(bro);
					extra_b = root;
				}
			}
		}
		extra_b->red_black = BLACK;
	}

	value_type*	begin()
	{	return &(_begin->value);	}

	value_type*	end()
	{	return &(_end->value);	}

	class	iterator{
		public:
		typedef std::bidirectional_iterator_tag	iterator_category;
		typedef	typename Alloc::value_type		value_type;
		typedef	typename Alloc::reference		reference;
		typedef	typename Alloc::pointer			pointer;
		typedef	typename Alloc::difference_type	difference_type;

		private:
		value_type	

		public:
		iterator();
		~iterator();
		
		bool	operator==(const iterator& other) const;
		bool	operator!=(const iterator& other) const;
		bool	operator<(const iterator& other) const;
		bool	operator<=(const iterator& other) const;
		bool	operator>(const iterator& other) const;
		bool	operator>=(const iterator& other) const;
		iterator&	operator=(const iterator& other);
		iterator&	operator++();
		iterator	operator++(int);
		iterator&	operator--();
		iterator	operator--(int);
		reference	operator*() const;
		pointer		operator->() const;
	
		



	};

	size_type	size() const{
		return (_size);
	}
	Value	at(const Key& key)	
	{
		node_pointer	node = search_key(key);

		if (node != nil)
			return (node->value.second);
		else
			throw(std::out_of_range("Map"));
	}

	size_type	max_size() const
	{return (std::numeric_limits<size_type>::max() / sizeof(node_type));}

};

int	main(void)
{
	RB_tree<int, std::string>	rb_tree;
	std::map<int, std::string>	map1;

	map1.insert(make_pair(1, (std::string)"1"));

	rb_tree.insert_node(make_pair(1, (std::string)"1"));
	rb_tree.insert_node(make_pair(2, (std::string)"2"));
	// rb_tree.insert_node(make_pair(5, (std::string)"5"));
	// rb_tree.insert_node(make_pair(4, (std::string)"4"));
	// rb_tree.insert_node(make_pair(3, (std::string)"3"));
	// rb_tree.insert_node(make_pair(6, (std::string)"6"));
	// rb_tree.insert_node(make_pair(8, (std::string)"8"));
	// rb_tree.insert_node(make_pair(7, (std::string)"7"));
	// rb_tree.insert_node(make_pair(10, (std::string)"10"));
	// rb_tree.insert_node(make_pair(11, (std::string)"11"));
	// rb_tree.insert_node(make_pair(9, (std::string)"9"));

	rb_tree.print_tree();
	std::cout << "size: " << rb_tree.size() << std::endl;

	rb_tree.delete_node(1);
	rb_tree.delete_node(2);
	rb_tree.delete_node(2);
	rb_tree.print_tree();
	std::cout << "size: " << rb_tree.size() << std::endl;

	rb_tree.insert_node(make_pair(1, (std::string)"1"));
	rb_tree.insert_node(make_pair(2, (std::string)"2"));
	rb_tree.print_tree();
	std::cout << "size: " << rb_tree.size() << std::endl;

	

	// system("leaks a.out");
	
}