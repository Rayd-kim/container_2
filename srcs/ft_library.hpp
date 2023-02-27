#ifndef FT_LIBRARY_HPP
#define	FT_LIBRARY_HPP

namespace ft{
	template <typename Iter>
	struct	iterator_traits{
		typedef typename	Iter::difference_type	difference_type;
		typedef typename	Iter::value_type		value_type;
		typedef typename	Iter::pointer			pointer;
		typedef typename	Iter::reference			reference;
		typedef typename	Iter::iterator_category	iterator_category;
		
	};

	template <typename T>
	struct iterator_traits<T*>{
		typedef	typename	std::ptrdiff_t					difference_type;
		typedef	T											value_type;
		typedef	T*											pointer;
		typedef	T&											reference;
		typedef typename	std::random_access_iterator_tag	iterator_category;
	};

	template <typename T>
	struct iterator_traits<const T*>{
		typedef typename	std::ptrdiff_t					difference_type;
		typedef	T											value_type;
		typedef	const T*									pointer;
		typedef	const T&									reference;
		typedef typename	std::random_access_iterator_tag	iterator_category;
	};

	template <typename Iter>
	class	reverse_iterator{
		public:
		typedef	Iter														iterator_type;
		typedef typename	ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename	ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename	ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename	ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename	ft::iterator_traits<Iter>::reference			reference;

		private:
			iterator_type	_iter;
		
		public:
		reverse_iterator() : _iter() {}
		explicit reverse_iterator(iterator_type it) : _iter(it) {}

		template <typename U>
		reverse_iterator (const reverse_iterator<U>& other): _iter(other.base()) {}
		iterator_type	base() const 
		{	return (_iter); }

		template <typename U>
		reverse_iterator&	operator=(const reverse_iterator<U>& other)
		{
			_iter = other.base();
			return (*this);
		}
		reference			operator*() const
		{
			iterator_type	temp = _iter;
			return *(--temp);
		}
		pointer				operator->() const
		{	return (&(operator*()));	}
		reference			operator[](difference_type n) const
		{	return (_iter[-n -1]);	}
		reverse_iterator	operator+(difference_type n) const
		{
			reverse_iterator	temp;

			temp._iter = _iter - n;
			return (temp);
		}
		reverse_iterator	operator-(difference_type n) const
		{
			reverse_iterator	temp;

			temp._iter = _iter + n;
			return (temp);
		}
		reverse_iterator&	operator++()
		{
			_iter = --_iter;
			return (*this);
		}
		reverse_iterator	operator++(int)
		{
			reverse_iterator	temp = *this;
			_iter = --_iter;
			return (temp);
		}
		reverse_iterator&	operator--()
		{
			_iter = ++_iter;
			return (*this);
		}
		reverse_iterator	operator--(int)
		{
			reverse_iterator	temp = *this;
			_iter = ++_iter;
			return (temp);
		}
		reverse_iterator&	operator+=(difference_type n)
		{
			_iter -= n;
			return (*this);
		}
		reverse_iterator&	operator-=(difference_type n)
		{
			_iter += n;
			return (*this);
		}
	};

	template <typename Iter1, typename Iter2>
	bool	operator==(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{	return lhs.base() == rhs.base();	}
	template <typename Iter1, typename Iter2>
	bool	operator!=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{	return lhs.base() != rhs.base();	}
	template <typename Iter1, typename Iter2>
	bool	operator<(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{	return lhs.base() > rhs.base();		}
	template <typename Iter1, typename Iter2>
	bool	operator<=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{	return lhs.base() >= rhs.base();	}
	template <typename Iter1, typename Iter2>
	bool	operator>(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{	return lhs.base() < rhs.base();		}
	template <typename Iter1, typename Iter2>
	bool	operator>=(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{	return lhs.base() <= rhs.base();	}

	template <typename Iter>
	reverse_iterator<Iter>	operator+(typename reverse_iterator<Iter>::difference_type n, const reverse_iterator<Iter>& other)
	{	return other + n;	}
	template <typename Iter1, typename Iter2>
	typename reverse_iterator<Iter1>::difference_type	operator-(const reverse_iterator<Iter1>& lhs, const reverse_iterator<Iter2>& rhs)
	{	return rhs.base() - lhs.base();	}


	template <bool, typename T = void >
	struct enable_if {};

	template <typename T>
	struct	enable_if<true, T>{
		typedef	T	type;
	};

	template <typename T>
	struct	is_integral{
		static const bool value = false;
	};

	template<>
	struct	is_integral<bool>{ static const bool value = true;};
	template<>
	struct	is_integral<char>{ static const bool value = true;};
	template<>
	struct	is_integral<char16_t>{ static const bool value = true;};
	template<>
	struct	is_integral<char32_t>{ static const bool value = true;};
	template<>
	struct	is_integral<wchar_t>{ static const bool value = true;};
	template<>
	struct	is_integral<signed char>{ static const bool value = true;};
	template<>
	struct	is_integral<short int>{ static const bool value = true;};
	template<>
	struct	is_integral<int>{ static const bool value = true;};
	template<>
	struct	is_integral<long int>{ static const bool value = true;};
	template<>
	struct	is_integral<long long int>{ static const bool value = true;};
	template<>
	struct	is_integral<unsigned char>{ static const bool value = true;};
	template<>
	struct	is_integral<unsigned short int>{ static const bool value = true;};
	template<>
	struct	is_integral<unsigned int>{ static const bool value = true;};
	template<>
	struct	is_integral<unsigned long int>{ static const bool value = true;};
	template<>
	struct	is_integral<unsigned long long int>{ static const bool value = true;};
	
	template <typename InputIt1, typename InputIt2>
	bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		while (first1 != last1)
		{
			if (*first1 != *first2)
				return (false);
			++first1;
			++first2;
		}
		return (true);
	};

	template <typename InputIt1, typename InputIt2, typename BinaryPredicate>
	bool	equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate pred)
	{
		for (; first1 != last1; ++first1, ++first2)
			if (!pred(*first1, *first2))
				return false;
		return true;
	};

	template <typename InputIt1, typename InputIt2>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (*first1 < *first2)
				return (true);
			if (*first1 > *first2)
				return (false);
		}
		if ((first1 == last1) && (first2 != last2)) //Iter1이 먼저 끝이면 true
			return (true);
		else
			return (false);
	};

	template <typename InputIt1, typename InputIt2, typename Compare>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, ++first2)
		{
			if (comp(*first1, *first2))
				return (true);
			if (comp(*first2, *first1))
				return (false);
		}
		if ((first1 == last1) && (first2 != last2))
			return (true);
		else
			return (false);
	};


	template <typename T1, typename T2>
	struct	pair{
		public:
		typedef	T1	first_type;
		typedef	T2	second_type;

		T1	first;
		T2	second;

		pair() : first(), second() {}

		template<typename U, typename V>
		pair(const pair<U, V>& pr) : first(pr.first), second(pr.second) {}

		pair(const first_type& a, const second_type& b) : first(a), second(b) {}

		pair&	operator=(const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		}
	};

	template <typename T1, typename T2>
	ft::pair<T1, T2>	make_pair(T1 first, T2 second)
	{
		return (ft::pair<T1, T2>(first, second));
	};
	
	template <typename T1, typename T2>
	bool	operator==(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{	return (lhs.first == rhs.first && lhs.second == rhs.second);	}
	template <typename T1, typename T2>
	bool	operator!=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{	return !(lhs == rhs);	}
	template <typename T1, typename T2>
	bool	operator<(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{	return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second));	}
	template <typename T1, typename T2>
	bool	operator<=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{	return !(lhs > rhs);	}
	template <typename T1, typename T2>
	bool	operator>(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{	return (rhs < lhs);	}
	template <typename T1, typename T2>
	bool	operator>=(const ft::pair<T1, T2>& lhs, const ft::pair<T1, T2>& rhs)
	{	return !(lhs < rhs);	}
	
	template<typename T>
	void	swap(T& a, T& b)
	{
		T	temp = a;
		a = b;
		b = temp;
	}

};


#endif