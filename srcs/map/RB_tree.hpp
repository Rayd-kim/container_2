#ifndef	RB_TREE_HPP
#define	RB_TREE_HPP

#include <iostream>
#include <stdexcept>
#include "RB_tree_iterator.hpp"
#include "../ft_library.hpp"

template<typename _pair, typename Compare = std::less<_pair>, 
typename Allocator = std::allocator<_pair> >
class RB_tree{
	public:
	typedef	_pair												value_type;
	typedef	Allocator											Alloc;
	typedef	Compare												key_compare;
	typedef	value_type&											reference;
	typedef	typename Allocator::size_type						size_type;
	typedef	Node<value_type>									node_type;
	typedef	node_type*											node_pointer;
	typedef	tree_iterator<_pair>								iterator;
	typedef	const_tree_iterator<_pair>							const_iterator;
	typedef	typename Allocator::template rebind<node_type>::other	Alnode;

	private:
		size_type		_size;
		node_pointer	root;
		node_pointer	nil;
		node_pointer	_begin;
		node_pointer	_end;
		Alnode			real_alloc;
		key_compare		_comp;
		Alloc			_alloc;

	public:
	RB_tree(const Compare& comp = key_compare(), const Allocator& alloc = Alloc()) : root(NULL), _comp(comp), _alloc(alloc)
	{
		nil = create_nil_node();

		_begin = nil;
		_end = nil;
		_size = 0;
	}

	RB_tree(const RB_tree& other) : root(NULL), _comp(other._comp), _alloc(other._alloc)
	{
		nil = create_nil_node();
		_begin = nil;
		_end = nil;
		_size = 0;

		iterator	start(other._begin, other.nil, other.root);
		iterator	end(other._end, other.nil, other.root);
		while (start != end)
			insert_node(*start++);
	}

	~RB_tree()
	{
		clear();
		real_alloc.deallocate(nil, 1);
	}

	RB_tree&	operator=(const RB_tree& other)
	{
		clear();
		real_alloc.deallocate(nil, 1);

		real_alloc = other.real_alloc;
		_alloc = other._alloc;
		_comp = other._comp;
		nil = real_alloc.allocate(1);

		iterator	start = iterator(other._begin, other.nil, other.root);
		iterator	end = iterator(other._end, other.nil, other.root);
		while (start != end)
			insert_node(*start++);
		return (*this);
	}
	node_pointer create_nil_node()
	{
		node_pointer	ret = real_alloc.allocate(1);

		ret->parent = NULL;
		ret->left = NULL;
		ret->right = NULL;
		ret->red_black = BLACK;
		return (ret);
	}

	node_pointer create_new_node(const value_type& pair)
	{
		node_pointer	ret = real_alloc.allocate(1);
		_alloc.construct(&(ret->value), pair);

		ret->parent = NULL;
		ret->left = nil;
		ret->right = nil;
		ret->red_black = RED;

		if (_begin == nil)
			_begin = ret;
		else if (_comp(pair, _begin->value))
			_begin = ret;
		return (ret);
	}

	ft::pair<iterator, bool>	insert_node(const value_type& pair)
	{
		if (root == NULL)
		{
			root = create_new_node(pair);
			root->red_black = BLACK;
			_size++;
			return ft::make_pair(iterator(root, nil, root), true);
		}

		node_pointer	ret = root;
		node_pointer	parent;

		while (ret != nil)
		{
			parent = ret;
			if (_comp(pair, ret->value))
				ret = ret->left;
			else if (_comp(ret->value, pair))
				ret = ret->right;
			else
				return ft::make_pair(iterator(ret, nil, root), false);
		}
		ret = create_new_node(pair);
		ret->parent = parent;
		if (_comp(pair, parent->value))
			parent->left = ret;
		else
			parent->right = ret;
		red_black_check(ret);
		_size++;
		return ft::make_pair(iterator(ret, nil, root), true);
	}
	node_pointer	max()
	{
		node_pointer	temp = root;
		if (temp == NULL)
			return nil;
		while (temp->right != nil)
			temp = temp->right;
		return temp;
	}
	node_pointer	Leftmost(node_pointer node)
	{
		if (node == nil)
			return nil;
		while (node->left != nil)
			node = node->left;
		return node;
	}
	node_pointer	Rightmost(node_pointer node)
	{
		if (node == nil)
			return nil;
		while (node->right != nil)
			node = node->right;
		return node;
	}
	node_pointer	next_node(node_pointer node)
	{
		if (node == nil) //end()일 때?
			return nil;
		
		if (node->right != nil)
			return Leftmost(node->right);
		
		node_pointer parent = node->parent;
		if (parent == NULL) //root인데 왼쪽 자식만 있을경우
			return nil;
		if (node == parent->left)
			return parent;

		while (parent != NULL && node != parent->left)
		{
			node = parent;
			parent = node->parent;
		}
		if (parent == NULL)
			return nil;
		return parent;
	}
	node_pointer	prev_node(node_pointer node)
	{
		if (node == nil) //node == end일 때
			return max();

		if (node->left != nil)
			return Rightmost(node->left);
		
		node_pointer parent	= node->parent;
		if (parent == NULL)
			return nil;
		if (node == parent->right)
			return parent;

		while (parent != NULL && node != parent->right)
		{
			node = parent;
			parent = node->parent;
		}
		if (parent == NULL)
			return nil;
		return parent;
	}
	void	left_rotate(node_pointer node)
	{
		node_pointer	temp_parent;
		node_pointer	node_left;

		node_left = node->left;  //node->left save
		temp_parent = node->parent->parent; //parent->parent save

		node->parent->right = node_left; //현재 노드의 부모노드의 오른쪽 노드를 현재 노드의 왼쪽으로 변경 
		if (node_left != nil)
			node_left->parent = node->parent;

		node->left = node->parent; // 현재 노드의 왼쪽이 부모노드를 가리키도록 변경
		if (node->left != nil)
			node->left->parent = node; // 원래 부모노드가 현재노드의 왼쪽으로 변경되었으므로, 원래 부모노드의 부모노드를 현재노드로 변경
		if (node != nil)
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
	void	right_rotate(node_pointer node)
	{
		node_pointer	temp_parent;
		node_pointer	node_right;


		node_right = node->right; // 현재노드의 오른쪽 저장
		temp_parent = node->parent->parent; // 현재부모노드의 부모노드(조부모노드)를 저장

		node->parent->left = node_right; // 부모노드의 왼쪽노드(현재노드임)를 현재노드의 오른쪽으로 변경
		if (node_right != nil)
			node_right->parent = node->parent;

		node->right = node->parent; // 현재 노드의 오른쪽이 부모노드를 가리키도록 변경
		if (node->right != nil)
			node->right->parent = node;
		if (node != nil)
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
	void	red_black_check(node_pointer node)
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
				node_pointer	node_parent = node->parent;
				node_pointer	node_grand_parent = node->parent->parent;

				if (node_parent->red_black == RED && node_grand_parent->right->red_black == RED)// 부모, 자식, 삼촌노드도 red 일 때.
				{
					node_parent->red_black = BLACK;
					node_grand_parent->right->red_black = BLACK;
					node_grand_parent->red_black = RED;
					red_black_check(node_grand_parent);
				}
				else if (node_grand_parent->right->red_black == BLACK && node == node_parent->right) //삼촌노드가 블랙이고, 자식이 부모의 오른쪽일때
				{
					left_rotate(node);
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
				node_pointer	node_parent = node->parent;
				node_pointer	node_grand_parent = node->parent->parent;

				if (node_parent->red_black == RED && node_grand_parent->left->red_black == RED)// 부모, 자식, 삼촌노드도 red 일 때.
				{
					node_parent->red_black = BLACK;
					node_grand_parent->left->red_black = BLACK;
					node_grand_parent->red_black = RED;
					red_black_check(node_grand_parent);
				}
				else if (node_grand_parent->left->red_black == BLACK && node == node_parent->left) //삼촌노드가 블랙이고, 자식이 부모의 왼쪽일때
				{
					right_rotate(node);
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
	node_pointer	search_key(const _pair& pair) const
	{
		node_pointer	ret = root;

		while (ret != nil && ret != NULL)
		{
			if (_comp(pair, ret->value))
				ret = ret->left;
			else if (_comp(ret->value, pair))
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
			node = node->right;
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
	void	delete_node(const _pair& pair)
	{
		node_pointer	node = search_key(pair);

		if (node != nil)
		{
			node_pointer			del = node;
			node_pointer			extra_b; //extra black을 갖게 될 node = 삭제되는 노드의 자식.
			int	del_origin_color	= node->red_black;

			if (node == _begin)// begin이 삭제될 때는, begin++을 가리키도록 재조정
			{
				_begin = next_node(_begin);
			}

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
			else //양쪽에 자식을 가질 때, successor의 부모가 node인지 아닌지에 따라서 재조정이 조금 달라진다.
			{
				del = search_successor(node->left);
				del_origin_color = del->red_black;
				extra_b = del->left; // successor는 오른쪽노드를 절대 가질리 없다. (그러면 그 오른쪽이 successor가 되기 때문에)
				
				if (del->parent == node)
					extra_b->parent = del;
				else
				{
					transplant(del, del->left);
					del->left = node->left;
					del->left->parent = del;
				}
				transplant(node, del);
				del->right = node->right;
				del->right->parent = del;
				del->red_black = node->red_black;
			}
			//fix_up
			if (del_origin_color == BLACK)
				fixed_up_rb_tree(extra_b);
				
			_alloc.destroy(&(node->value));
			real_alloc.deallocate(node, 1);
			_size--;
		}
		nil->parent = NULL;
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

	size_type	size() const{
		return (_size);
	}
	value_type&	at(const _pair& pair)
	{
		node_pointer	node = search_key(pair);

		if (node != nil)
			return (node->value);
		else
			throw(std::out_of_range("Map"));
	}
	size_type	max_size() const
	{	return (std::numeric_limits<size_type>::max() / sizeof(node_type));	}
	
	iterator	find(const value_type& value, iterator begin, iterator end)
	{
		while (begin != end)
		{
			if (begin->first == value.first)
				return (begin);
			++begin;
		}
		return (begin);
	}
	const_iterator	find(const value_type& value, const_iterator begin, const_iterator end) const
	{
		while (begin != end)
		{
			if (begin->first == value.first)
				return (begin);
			++begin;
		}
		return (begin);
	}
	size_type	count(const value_type& value) const
	{
		node_pointer	node = search_key(value);

		if (node == nil)
			return (0);
		return (1);
	}
	void	clear()
	{
		node_pointer	next, remove;

		remove = _begin;
		next = next_node(remove);
		while (remove != nil)
		{
			delete_node(remove->value);
			remove = next;
			next = next_node(remove);
		}
	}
	size_type	erase(const value_type& value)
	{
		node_pointer	remove = search_key(value);

		if (remove == nil)
			return (0);
		delete_node(value);
		return (1);
	}
	void	swap(RB_tree& other)
	{
		ft::swap (root, other.root);
		ft::swap (nil, other.nil);
		ft::swap (_begin, other._begin);
		ft::swap (_end, other._end);
		ft::swap (_comp, other._comp);
		ft::swap (_alloc, other._alloc);
		ft::swap (real_alloc, other.real_alloc);
		ft::swap (_size, other._size);
	}
	node_pointer	get_nil() const
	{	return (nil);	}
	node_pointer	get_root() const
	{	return (root);	}
	node_pointer	get_begin() const
	{	return (_begin);	}
	node_pointer	get_end() const
	{	return (_end);	}
};

#endif