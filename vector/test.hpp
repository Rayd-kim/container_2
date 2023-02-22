#ifndef VECTOR_TEST
#define VECTOR_TEST

#include <iostream>
#include <memory>
#include <exception>

namespace ft
{
	template < typename T, class Alloc = std::allocator<T> >
	class vector {
		private:
			T* 		_data;
			size_t	_length;
			size_t	_capacity;
			Alloc	alloc;

		public:
			typedef	T 												value_type;
			typedef	Alloc 											allocator_type;
			typedef	T&												reference;
			typedef	typename std::allocator_traits<Alloc>::pointer	pointer;
			typedef	typename std::allocator<T>::difference_type		difference_type;
			typedef	typename std::allocator<T>::size_type			size_type;

		void	remove(size_t index);
		// 	//기본생성자
		// 	explicit vector() : _length(0), _capacity(0){
		// 		_data = nullptr;
		// 	}
		// 	// n 만큼의 v를 가지는 벡터. n 만 들어오면 v는 기본값 T()가 된다. 속도향상을 위해 T의 복사생성자로 붙여넣기.
		// 	explicit vector(size_type n, const T& v = T()) : _length(n), _capacity(n) {
		// 		_data = alloc.allocate(n);
		// 		for (size_type i = 0; i < n; i++)
		// 			_data[i] = T(v);
		// 	}

		// 	// 복사생성자
		// 	//vector(const vector &other) : {}

		// 	//iterator 생성자
		// 	//vector(const_iterator first, const_iterator last): {};

		// 	void	push_back(const T& element) //새로운 원소 추가
		// 	{
		// 		if (_capacity <= _length)
		// 		{
		// 			if (_capacity == 0) // 기본생성자로 생성시, capacity가 0이기 때문에 예외처리
		// 				_capacity += 1;

		// 			T *temp = alloc.allocate(_capacity * 2);

		// 			alloc.construct(&temp[0], _data[0]); //_data 는  맨앞을 가리키고 있으니까 오류를 피하기위해 0은 따로.
		// 			for (size_t i = 1; i < _length; i++)
		// 			{
		// 				alloc.construct(&temp[i], _data[i]);
		// 				alloc.destroy(&_data[i]);
		// 			}

		// 			alloc.destroy(_data);
		// 			alloc.deallocate(_data, _capacity);
		// 			_data = temp;
		// 			_capacity *= 2;
		// 		}
		// 		alloc.construct(&_data[_length], element);
		// 		_length++;
		// 	}

		// 	void	remove(size_t index) //index번째 위치한 원소를 제거
		// 	{
		// 		alloc.destroy(&_data[index]);
		// 		for (size_t i = index + 1; i < _length; i++)
		// 			_data[i - 1] = _data[i];
		// 		_length--;
		// 	}

		// 	//Element access (at, operator[], front, back, _data)

		// 	T&	at(size_t index)
		// 	{
		// 		if (index >= _length)
		// 		{
		// 			throw (std::out_of_range("vector"));
		// 		}
		// 		return _data[index];
		// 	}

		// 	T operator[](size_t index) //index 번째 원소에 접근
		// 	{
		// 		return _data[index];
		// 	}

		// 	//front back 함수는 비어있을 경우 segmentation fault 떠야한다.. cppreference에서 c.front() = *c.begin() 이다.
		// 	// iterator를 반환하도록 만들어야하나..?
		// 	T&	front()
		// 	{	return (_data[0]);	}

		// 	T&	back()
		// 	{	return (_data[_length - 1]);	}

		// 	T*	data()
		// 	{
		// 		if (_length == 0)
		// 			return (nullptr);
		// 		return (_data);
		// 	}

		// 	size_t	size() //vector의 크기 (vector에 할당된 크기가 아닌 데이터가 저장된 크기)
		// 	{	return _length;	}

		// 	size_t	capacity()
		// 	{	return _capacity;	}

		// 	bool	empty()
		// 	{
		// 		if (_length == 0)
		// 			return (true);
		// 		else
		// 			return (false);
		// 	}

		// 	~vector()
		// 	{
		// 		if (_data != nullptr)
		// 		{
		// 			for (size_t i = 0; i < _length; i++)
		// 				alloc.destroy(&_data[i]);
		// 			alloc.deallocate(_data, _capacity);
		// 		}
		// 	}

		// 	class	iterator{
		// 	private:
		// 		vector<T>*	_vec;
		// 		T*			_vec_data;
		// 		size_t		_index;

		// 	public:
		// 		typedef	std::random_access_iterator_tag	iterator_category;
		// 		typedef	typename Alloc::value_type		value_type;
		// 		typedef	typename Alloc::reference		reference;
		// 		typedef	typename Alloc::pointer			pointer;
		// 		typedef	typename Alloc::difference_type	difference_type;

		// 		iterator();
		// 		iterator(vector<T>* vec, T* vec_data, size_t index) :
		// 		_vec(vec), _vec_data(vec_data), _index(index) {}
		// 		~iterator() {}

		// 		T& operator*()
		// 		{
		// 			return (_vec_data[_index]);
		// 		}

		// 	};

		// 	iterator begin()
		// 	{
		// 		return iterator(this, _data, 0);
		// 	}

	};
};

template < typename T, class U >
void	ft::vector<T, U>::remove(size_t index) //index번째 위치한 원소를 제거
{
	alloc.destroy(&_data[index]);
	for (size_t i = index + 1; i < _length; i++)
		_data[i - 1] = _data[i];
	_length--;
}


#endif