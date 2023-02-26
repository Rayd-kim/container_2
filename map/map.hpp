#ifndef	MAP_HPP
#define	MAP_HPP

#include "RB_tree.hpp"
#include "../ft_library.hpp"

namespace ft{

template< typename Key, typename T, typename Compare = std::less<Key>,
typename Allocator = std::allocator<ft::pair<const Key, T> > >
class map{

	public:

	typedef	Key										key_type;
	typedef	T										mapped_type;
	typedef	ft::pair<const Key, T>					value_type;
	typedef	Compare									key_compare;
	typedef	Allocator								allocator_type;
	typedef	value_type&								reference;
	typedef	const value_type&						const_reference;
	typedef	typename Allocator::pointer				pointer;
	typedef	typename Allocator::const_pointer		const_pointer;
	typedef	typename Allocator::size_type			size_type;
	typedef	typename Allocator::difference_type		difference_type;
	// typedef	tree_iterator<value_type>				iterator;
	// typedef	tree_iterator<const value_type>			const_iterator;
	class value_compare{
		protected:
			Compare comp;
			value_compare(Compare c) : comp(c) {}

		public:		
			bool operator()(const value_type& lhs, const value_type& rhs) const{
				return comp(lhs.first, rhs.first);
			}
		friend	class map;
	};
	
	typedef	RB_tree<value_type, value_compare, Allocator>	rb_tree;

	typedef	typename rb_tree::iterator				iterator;
	typedef	typename rb_tree::const_iterator		const_iterator;
	typedef	ft::reverse_iterator<iterator>			reverse_iterator;
	typedef	ft::reverse_iterator<const_iterator>	const_reverse_iterator;


	private:

	public:
		rb_tree			_tree;
		key_compare		_comp;
		allocator_type	_alloc;

	//constructor & destructor
	// map() : _tree() , _comp(Compare()), _alloc(Allocator()){};
	~map() {};

	explicit map(const Compare& comp = Compare(), const Allocator& alloc = Allocator() )
	: _tree(rb_tree(comp, alloc)), _comp(comp), _alloc(alloc){};
	
	template<class InputIt>
	map(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
	: _tree(rb_tree(comp, alloc)), _comp(comp), _alloc(alloc)
	{
		while (first != last)
		{
			_tree.insert_node(*first);
			first++;
		}
	}

	map(const map& other) : _tree(rb_tree(other._tree)), _comp(other._comp), _alloc(other._alloc) {}

	map& operator=(const map& other)
	{
		_tree = other._tree;
		_comp = other._comp;
		_alloc = other._alloc;
		return *this;
	}

	// member function
	allocator_type	get_allocator() const //Returns the allocator associated with the container
	{	return (_alloc);	}
	T& at(const Key& key) //if no such element exists, an exception of type std::out_of_range is thrown.
	{	return _tree.at(ft::make_pair(key, mapped_type())).second;	}
	const T& at(const Key& key) const
	{	return _tree.at(ft::make_pair(key, mapped_type())).second;	}
	T& operator[](const Key& key)
	{
		iterator	iter = insert(ft::make_pair(key, mapped_type())).first;
		return (*iter).second;
	}
	bool empty() const
	{
		if (_tree.size() == 0)
			return true;
		return false;
	}
	size_type size() const
	{	return _tree.size();	}
	size_type max_size() const
	{	return _tree.max_size();	}	
	ft::pair<iterator, bool> insert(const value_type& value)
	{	return (_tree.insert_node(value));	}
	iterator insert(iterator pos, const value_type& value)
	{
		iterator tmp = pos;
		return _tree.insert_node(value).first;
	}

	template<class InputIt>
	void insert(InputIt first, InputIt last)
	{
		while (first != last)
			insert(*first++);
	}
	
	void clear() //vector 랑 다르게 capacity는 없으니까, size만 0으로
	{	_tree.clear();	}
	
	void erase(iterator pos)
	{	_tree.delete_node(*pos);	}

	void erase(iterator first, iterator last)
	{
		while (first != last)
			erase(first++);
	}
	size_type erase(const Key& key) // Removes the element(if one exists) with the key equivalent to key.
	{	return _tree.erase(ft::make_pair(key, mapped_type()));	}
	

	void swap(map& other)
	{
		_tree.swap(other._tree);
		ft::swap(_comp, other._comp);
		ft::swap(_alloc, other._alloc);
	}

	size_type count(const Key& key) const //key에 해당하는 값이 몇개있는지. 0 or 1 중 하나임(중복을 허용하지 않기 때문에)
	{
		return (_tree.count(ft::make_pair(key, mapped_type())));
	}
	
	iterator find(const Key& key)
	{
		return (_tree.find(ft::make_pair(key, mapped_type()), begin(), end()));
	}
	const_iterator find(const Key& key) const
	{
		return (_tree.find(ft::make_pair(key, mapped_type()), begin(), end()));
	}
	
	ft::pair<iterator, iterator> equal_range(const Key& key)
	{	return (ft::make_pair(lower_bound(key), upper_bound(key)));	}
	ft::pair<const_iterator, const_iterator> equal_range(const Key& key) const
	{	return (ft::make_pair(lower_bound(key), upper_bound(key)));	}

	iterator lower_bound(const Key& key)
	{	
		iterator	_begin = begin();

		while(_begin != end())
		{
			if (key <= _begin->first)
				return _begin;
			++_begin;
		}
		return _begin;
	}
	const_iterator lower_bound(const Key& key) const
	{
		const_iterator	_begin = begin();

		while(_begin != end())
		{
			if (key <= _begin->first)
				return _begin;
			++_begin;
		}
		return _begin;
	}
	iterator upper_bound(const Key& key)
	{
		iterator	_begin = begin();

		while(_begin != end())
		{
			if (key < _begin->first)
				return _begin;
			++_begin;
		}
		return _begin;
	}
	const_iterator upper_bound(const Key& key) const
	{
		const_iterator	_begin = begin();

		while(_begin != end())
		{
			if (key < _begin->first)
				return _begin;
			++_begin;
		}
		return _begin;
	}
	

	
	
	key_compare	key_comp() const
	{	return _comp;	}

	value_compare	value_comp() const
	{	return value_compare(_comp);	}

	iterator	begin()
	{	return iterator(_tree.get_begin(), _tree.get_nil(), _tree.get_root());	}
	iterator	end()
	{	return iterator(_tree.get_end(), _tree.get_nil(), _tree.get_root());	}
	const_iterator	begin() const
	{	return const_iterator(_tree.get_begin(), _tree.get_nil(), _tree.get_root());	}
	const_iterator	end() const
	{	return const_iterator(_tree.get_end(), _tree.get_nil(), _tree.get_root());	}
	reverse_iterator	rbegin()
	{	return reverse_iterator(end());	}
	reverse_iterator	rend()
	{	return reverse_iterator(begin());	}
	const_reverse_iterator	rbegin() const
	{	return const_reverse_iterator(end());	}
	const_reverse_iterator	rend() const
	{	return const_reverse_iterator(begin());	}

};

//non-member function
template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator==(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	else
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
}
template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator!=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{	return !(lhs == rhs);	}
template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator<(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{	return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());	}
template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator<=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{	return !(rhs < lhs);	}
template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator>(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{	return (rhs < lhs);	}
template <typename Key, typename T, typename Compare, typename Alloc>
bool	operator>=(const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& rhs)
{	return !(lhs < rhs);	}

template< class Key, class T, class Compare, class Alloc >
void swap( ft::map<Key, T, Compare, Alloc>& lhs,  ft::map<Key, T, Compare, Alloc>& rhs )
{	lhs.swap(rhs);	}

};

#endif