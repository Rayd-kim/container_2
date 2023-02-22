#ifndef	VECTOR_ITERATOR_HPP
#define	VECTOR_ITERATOR_HPP

#include "vector.hpp"
#include <memory>

template <typename T, typename Alloc = std::allocator<T> >
class	iterator{
			private:
				vector<T>*	_vec;
				T*			_vec_data;
				size_type	_index;

			public:
				typedef	std::random_access_iterator_tag	iterator_category;
				typedef	typename Alloc::value_type		value_type;
				typedef	typename Alloc::reference		reference;
				typedef	typename Alloc::pointer			pointer;
				typedef	typename Alloc::difference_type	difference_type;

				iterator(): _vec(nullptr), _vec_data(nullptr), _index(0) {}
				iterator(vector<T>* vec, T* vec_data, size_type index)
				:_vec(vec), _vec_data(vec_data), _index(index) {}
				~iterator() {}

				bool		operator==(const iterator& iter) const
				{	return (this->_vec_data[this->_index] != iter._vec_data[iter._index]);	}
				bool		operator!=(const iterator& iter) const
				{	return (this->_vec_data[this->_index] == iter._vec_data[iter._index]);	}
				bool		operator<(const iterator& iter) const
				{
					if (&this->_vec_data[this->_index] - &iter._vec_data[iter._index] < 0)
						return true;
					else
						return false;
				}
				bool		operator>(const iterator& iter) const
				{
					if (&this->_vec_data[this->_index] - &iter._vec_data[iter._index] > 0)
						return true;
					else
						return false;
				}
				bool		operator<=(const iterator& iter) const
				{
					if (&this->_vec_data[this->_index] - &iter._vec_data[iter._index] <= 0)
						return true;
					else
						return false;
				}
				bool		operator>=(const iterator& iter) const
				{
					if (&this->_vec_data[this->_index] - &iter._vec_data[iter._index] >= 0)
						return true;
					else
						return false;
				}
				iterator&	operator=(const iterator& iter)
				{
					this->_vec = iter._vec;
					this->_vec_data = iter._vec_data;
					this->_index = iter._index;
					return (*this);
				}
				iterator&	operator++()
				{
					this->_vec_data += 1;
					return (*this);
				}
				iterator	operator++(int)
				{
					iterator	temp;

					temp = *this;
					this->_vec_data += 1;
					return (temp);
				}
				iterator&	operator--()
				{
					this->_vec_data -= 1;
					return (*this);
				}
				iterator	operator--(int)
				{
					iterator	temp;

					temp = *this;
					this->_vec_data -= 1;
					return (temp);
				}
				iterator&	operator+=(size_type index)
				{
					_index += index;
					return (*this);
				}
				iterator&	operator-=(size_type index)
				{
					_index -= index;
					return (*this);
				}
				iterator	operator+(size_type	index) const
				{
					iterator	temp;

					temp._vec = this->_vec;
					temp._vec_data = this->_vec_data;
					temp._index = this->_index + index;
					return (temp);
				}
				iterator	operator-(size_type	index) const
				{
					iterator	temp;
				
					temp._vec = this->_vec;
					temp._vec_data = this->_vec_data;
					temp._index = this->_index - index;
					return (temp);
				}

				difference_type	operator-(iterator& iter) const
				{	return (this->_vec_data[this->_index] - iter._vec_data[iter._index]);	}
				reference	operator*() const
				{	return (_vec_data[_index]);	}
				pointer		operator->() const
				{	return (&_vec_data[_index]);	}
				reference	operator[](size_type index) const
				{	return (this->_vec_data[index]);	}
};


#endif