#ifndef LIST_DEMO_H
#define  LIST_DEMO_H


template <class T>
struct _list_node
{
	typedef void* void_ptr;
	void_ptr prev;
	void_ptr next;
	T data;
};

template<class T,class Ref,class Ptr>
struct _list_iterator
{
	typedef _list_iterator<T, T&, T*> iterator;
	typedef _list_iterator<T, Ref, Ptr> self;
	typedef bidirectional_iterator_tag iterator_category;
	typedef T value_type;
	typedef _list_node<T>* link_type;
	typedef size_t size_type;
	typedef ptrdiff_t dufference_type;

	link_type node;
	//constructor
	_list_iterator(link_type x) :node(x){}
	_list_iterator(){}
	_list_iterator(const iterator&x) :node(x.node){}
	bool operator==(const self& x)const { return node == x.node; }
	bool operator!=(const self&x)const { return node != x.node; }
	reference operator*()const{ return (*node).datal; }
	pointer operator->()const { return &(operator* ()); }
	self& operator++()
	{
		node = (link_type)((*node).next);
		return *this;
	}
	self operator++(int)
	{
		self tmp = *this;
		++*this;
		return tmp;
	}

	self& operator--()
	{
		node = (link_type)((*node), prev);
		return *this;
	}
	self operator--(int)
	{
		self tmp = *this;
		--*this;
		return tmp;
	}
};
template <class T,class Alloc = alloc>
class list_demo
{
protected:
	typedef _list_node <T> list_node;
	typedef simple_alloc<list_node, Alloc >  list_node_allocator;
	link_type get_node(){ return list_node_allocator::allocate(); }
	void put_node(link_type p){ list_node_allocator::deallocate(p); }
	link_type create_node(const T& x)
	{
		link_type p = get_node();
		construct(&p->data, x);
		return p;
	}
	void destroy_node(link_type p)
	{
		destroy(&p->data);
		put_node(p);
	}
	void empty_initialize()
	{
		node = get_node();
		node->next = node;
		node->prev = node;
	}
public:
	list_demo(){ empty_initialize(); }
	typedef list_node* link_type;
protected:
	link_type node;
public:
	iterator begin(){ return (link_type)((*node).next); }
	iterator end(){ return node; }
	bool empty(){ return node->next == node; }
	size_type size() const
	{
		size_type result = 0;
		distance(begin(), end(), result);
		return result;
	}
	reference front(){ return *begin(); }
	reference back(){ return *(--end()); }
	iterator insert(iterator position, const T& x)
	{
		link_type tmp = create_node(x);
		tmp->next = position.node;
		tmp->prev = position.node->prev;
		(link_type(position.node->prev))->next = tmp;
		position.node->prev = tmp;
		return tmp;
	}
	void push_back(const T& x){ insert(end(), x); }
	void push_front(const T& x){ insert(begin(), x); }
	iterator erase(iterator position)
	{
		link_type next_node = link_type(position.node->next);
		link_type prev_node = link_type(position.node->prev);
		prev_node->next = next_node;
		next_node->prev = prev_node;
		destroy_node(position.node);
		return iterator(next_node);
	}
	void pop_front()
	{
		erase(begin());
	}
	void pop_back()
	{
		iterator tmp = end();
		erase(--tmp);
	}
	template<class T,class Alloc>
	void list_demo<T, Alloc>::clear()
	{
		link_type cur = (link_type)node->next;
		while (cur!= node)
		{
			link_type tmp = cur;
			cur = (link_type)cur->next;
			destroy_node(tmp);
		}
		node->next = node;
		node->prev = node;
	}
	template <class T,class Alloc>
	void list_demo<T, Alloc>::remove(const T& value)
	{
		iterator first = begin();
		iterator last = end();
		while (first != last)
		{
			iterator next = first;
			++next;
			if (*first == value) erase(first);
			first = next;
		}
	}
	template <class T, class Alloc>
	void list_demo<T, Alloc>::unique()
	{
		iterator first = begin();
		iterator last = end();
		if (first == last) return;
		iterator next = first;
		while (++next != last)
		{
			if (*first == *next)
				erase(next);
			else
				first = next;
			next = first;
		}
	
	}
};

#endif // LIST_DEMO_H
