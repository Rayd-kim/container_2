#ifndef RB_TREE_ITERATOR_HPP
#define RB_TREE_ITERATOR_HPP

#define RED 			1
#define BLACK			2

#include <iostream>

template <typename _pair>
struct Node {
	_pair	value;
	Node	*parent;
	Node	*left;
	Node	*right;
	int		red_black;
};

template <typename _pair>
class	tree_iterator{
	public:
	typedef std::bidirectional_iterator_tag		iterator_category;
	typedef	_pair								value_type;
	typedef	value_type&							reference;
	typedef	value_type*							pointer;
	typedef	std::ptrdiff_t						difference_type;
	typedef	Node<value_type>*					node_pointer;

	private:
	node_pointer		_node;

	public:
	node_pointer		_nil;
	node_pointer		_root;
	

	public:
	tree_iterator() : _node(), _nil(), _root() {}
	tree_iterator(node_pointer node, node_pointer nil, node_pointer root): _node(node), _nil(nil), _root(root) {}
	
	node_pointer	base() const
	{	return (_node); }

	tree_iterator&	operator++()
	{
		if (_node == _nil)
			return (*this);
		
		if (_node->right != _nil)
		{
			_node = _node->right;
			while (_node->left != _nil)
				_node = _node->left;
			return (*this);
		}

		node_pointer parent = _node->parent;
		if (parent == NULL)
		{
			_node = _nil;
			return (*this);
		}
		if (_node == parent->left)
		{
			_node = parent;
			return (*this);
		}
		while (parent != NULL && _node != parent->left)
		{
			_node = parent;
			parent = _node->parent;
		}
		if (parent == NULL)
		{
			_node = _nil;
			return (*this);
		}
		_node = parent;
		return (*this);
	}
	tree_iterator	operator++(int)
	{
		tree_iterator	temp = *this;
		operator++();
		return temp;
	}
	tree_iterator&	operator--()
	{
		if (_node == _nil)
		{
			node_pointer temp = _root;
			while (temp != NULL && temp->right != _nil)
				temp = temp->right;
			if (temp != NULL)
				_node = temp;
			return (*this); 
		}
		if (_node->left != _nil)
		{
			_node = _node->left;
			while (_node->right != _nil)
				_node = _node->right;
			return (*this);
		}

		node_pointer parent = _node->parent;
		if (parent == NULL)
		{
			_node = _nil;
			return (*this);
		}
		if (_node == parent->right)
		{
			_node = parent;
			return (*this);
		}
		while (parent != NULL && _node != parent->right)
		{
			_node = parent;
			parent =_node->parent;
		}
		if (parent == NULL)
		{
			_node = _nil;
			return (*this);
		}
		_node = parent;
		return (*this);
	}
	tree_iterator	operator--(int)
	{
		tree_iterator	temp = *this;
		operator--();
		return temp;
	}
	reference	operator*() const
	{	return (_node->value);	}
	pointer		operator->() const
	{	return &(_node->value);	}

	bool	operator==(const tree_iterator& other) const
	{	return _node == other._node;	}
	bool	operator!=(const tree_iterator& other) const
	{	return !(*this == other);	}

};

template <typename _pair>
class	const_tree_iterator{
	public:
	typedef std::bidirectional_iterator_tag		iterator_category;
	typedef	_pair								value_type;
	typedef const value_type					const_value_type;	
	typedef	const_value_type&					reference;
	typedef	const_value_type*					pointer;
	typedef	std::ptrdiff_t						difference_type;
	typedef	Node<value_type>*					node_pointer;

	private:
	node_pointer		_node;

	public:
	node_pointer		_nil;
	node_pointer		_root;
	
	public:
	const_tree_iterator() : _node(), _nil(), _root() {}
	const_tree_iterator(node_pointer node, node_pointer nil, node_pointer root): _node(node), _nil(nil), _root(root) {}
	const_tree_iterator(const tree_iterator<_pair>& other) : _node(other.base()), _nil(other._nil), _root(other._root) {}
	
	node_pointer	base() const
	{	return (_node); }

	const_tree_iterator&	operator++()
	{
		if (_node == _nil)
			return (*this);
		
		if (_node->right != _nil)
		{
			_node = _node->right;
			while (_node->left != _nil)
				_node = _node->left;
			return (*this);
		}

		node_pointer parent = _node->parent;
		if (parent == NULL)
		{
			_node = _nil;
			return (*this);
		}
		if (_node == parent->left)
		{
			_node = parent;
			return (*this);
		}
		while (parent != NULL && _node != parent->left)
		{
			_node = parent;
			parent = _node->parent;
		}
		if (parent == NULL)
		{
			_node = _nil;
			return (*this);
		}
		_node = parent;
		return (*this);
	}
	const_tree_iterator	operator++(int)
	{
		const_tree_iterator	temp = *this;
		operator++();
		return temp;
	}
	const_tree_iterator&	operator--()
	{
		if (_node == _nil)
		{
			node_pointer temp = _root;
			while (temp != NULL && temp->right != _nil)
				temp = temp->right;
			if (temp != NULL)
				_node = temp;
			return (*this); 
		}
		if (_node->left != _nil)
		{
			_node = _node->left;
			while (_node->right != _nil)
				_node = _node->right;
			return (*this);
		}

		node_pointer parent = _node->parent;
		if (parent == NULL)
		{
			_node = _nil;
			return (*this);
		}
		if (_node == parent->right)
		{
			_node = parent;
			return (*this);
		}
		while (parent != NULL && _node != parent->right)
		{
			_node = parent;
			parent =_node->parent;
		}
		if (parent == NULL)
		{
			_node = _nil;
			return (*this);
		}
		_node = parent;
		return (*this);
	}
	const_tree_iterator	operator--(int)
	{
		const_tree_iterator	temp = *this;
		operator--();
		return temp;
	}
	reference	operator*() const
	{	return (_node->value);	}
	pointer	operator->() const
	{	return &(_node->value);	}

	bool	operator==(const const_tree_iterator& other) const
	{	return _node == other._node;	}
	bool	operator!=(const const_tree_iterator& other) const
	{	return !(*this == other);	}
};


#endif