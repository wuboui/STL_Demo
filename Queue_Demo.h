#ifndef _QUEUE_DEMO_H
#define  _QUE_DEMO_H
template <class T,class Sequence = deque_demo<T>>
class queue_demo
{
	friend bool operator==__STL_NULL_TMPL_ARGS(const queue_demo&x, const queue_demo&y);
	friend bool operator<__STL_NULL_TMPL_ARGS(const queue_demo&x, const queue_demo&y);
public:
	typedef typename Sequence::value_type value_type;
	typedef typename Sequence::size_type size_type;
	typedef typename Sequence::reference reference;
	typedef typename Sequence::const_reference const_reference;
protected:
	Sequence c;
public:
	bool empty()const { return c.empty(); }
	size_type size() const { return c.size(); }
	reference front(){ return c.front(); }
	const_reference front()const { return c.front(); }
	reference back(){ return c.back(); }
	const_reference back()const { return c.back(); }
	void push(const value_type&x){ c.push_back(x); }
	void pop(){ c.pop_front(); }
};
template<class T,class Sequence>
bool operator== (const queue_demo <T,Sequence> &x,const queue_demo<T,Sequence>&y)
{
	return x.c == y.c;
}
template < class T,class Sequence >
bool operator<(const queue_demo<T, Sequence>&x, const queue_demo<T, Sequence>&y)
{
	return x.c < y.c;
}
#endif