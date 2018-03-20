#ifndef _PRIORITY_QUEUE_H_
#define _PRIORITY_QUEUE_H_
#include"Vector_demo.h"
template<class T,class Sequence = vector_demo<T>,class Compare = less<typename Sequence::value_type>>
class priority_queue_demo
{
public:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;
	typedef typename Sequence::const_reference const_reference;
protected:
	Sequence c;
	Compare comp;
public:
	priority_queue_demo() :c(){}
	explicit priority_queue_demo(const Compare&x) :c(), comp(x){}
	template<class InputIterator>
	priority_queue_demo(InputIterator first, InputIterator last, const Compare& x)
		: c(first, last), comp(x)
	{
		make_heap(c.begin(), c.end(), comp);
	}
	template<class InputIterator>
	priority_queue_demo(InputIterator first, InputIterator last)
		: c(first, last)
	{
		make_heap(c.begin(), c.end(), comp);
	}
	bool empty()const{ return c.empty(); }
	size_type size() const { return c.size(); }
	const_reference top()const { return c.front(); }
	void push(const value_type& x)
	{
		__STL_TRY
		{
			c.push_back(x);
			push_heap(c.begin(), c.end(), comp);
		}
		__STL_UNWIND(c.clear());
	}
	void pop()
	{
		__STL_TRY
		{
			pop_heap(c.begin(), c.end(), comp);
			c.pop_back();
		}
		__STL_UNWIND(c.clear());
	}
};
#endif