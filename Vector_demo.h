#ifndef _VECTOR_DEMO_H
#define  _VECTOR_DEMO_H
#include <memory.h>
template < class T, class Alloc = alloc >
class vector_demo
{
public:
	typedef T value_type;
	typedef value_type*  pointer;
	typedef value_type* iterator;
	typedef value_type& reference;
	typedef size_t size_type;
	typedef ptrdiff_t   differnce_type;
protected:
	typedef simple_alloc<value_type, Alloc> data_allocator;
	iterator start;
	iterator finish;
	iterator end_of_storage;
	void insert_aux(iterator position, const T& x);
	void deallocate()
	{
		if (start)
			data_allocator::deallocate(start, end_of_storage - start);
	}

	void fill_initialize(size_type n, conse T& value)
	{
		start = allocate_and_fill(n, value);
		finish = start + n;
		end_of_storage = finish;
	}
public:
	iterator begin(){ return start; }
	iterator end(){ return finish; }
	size_type size() const { return size_type(end() - begin()); }
	size_type capacity() const 
	{
		return size_type(end_of_storage - begin());
	}
	bool empty() const{ return begin() == end(); }
	reference operator[](size_type n){ return *(begin() + n); }
	vector_demo() :start(0), finish(0), end_of_storage(0){}
	vector_demo(size_type n, const T& value){ fill_initialize(n, value); }
	vector_demo(int n, const T& value){ fill_initialize(n, value); }
	vector_demo(long n, const T& value){ fill_initialize(n, value); }
	explicit vector_demo(size_type n){ fill_initialize(n, T()); }
	~vector_demo()
	{
		destroy(start, finish);
		deallocate();
	}
	reference front(){ return *begin(); }
	reference back(){ return *(end() - 1); }
	void push_back(const T& x)
	{
		if (finish !- end_of_storage)
		{
			construct(finish, x);
			++finish;
		}
		else
			insert_aux(end(), x);
	}
	void pop_back()
	{
		--finish;
		destroy(finish);
	}
	iterator erase(iterator position)
	{
		if (position + 1 != end())
			copy(position + 1, finish, position);
		--finish;
		destroy(finish);
		return position;
	}
	void resize(size_type new_size, const T& x)
	{
		if (new_size < size())
			erase(begin() + new_size, end());
		else
			insert(end(), new_size - size(), x);
	}
	void resize(size_type new_size)
	{
		resize(new_size, new T());
	}
	void clear()
	{
		erase(begin(), end());
	}

protected:
	iterator allocate_and_fill(size_type n, const T& x)
	{
		iterator result = data_allocator::allocate(n);
		uninitialized_fill_n(result, n, x);
		return result;
	}
};

template < class T, class Alloc /*= alloc */>
void vector_demo<T, Alloc>::insert_aux(iterator position, const T& x)
{
	if (finish != end_of_storage)
	{
		construct(finish, *(finish - 1));
		++finish;
		T x_copy = x;
		copy_backward(position, finish - 2, finish - 1);
		*position = x_copy;
	}
	else
	{
		const size_type old_size = size();
		const size_type len = old_size != 0 ? 2 * old_size : 1;
		iterator new_start = data_allocator::allocate(len);
		iterator new_finish = new_start;
		try
		{
			new_finish = uninitialized_copy(start, position, new_start);
			construct(new_finish, x);
			++new_finish;
			new_finish = uninitialized_copy(position, finish, new_finish);
		}
		catch (...)
		{
			destroy(new_start, new_finish);
			data_allocator::deallocate(new_start, len);
			throw;
		}
		destroy(begin(), end());
		deallocate();
		start = new_start;
		finish = new_finish;
		end_of_storage = new_start + len;
	}
}

#endif // !_VECTOR_DEMO_H
