#ifndef HASH_TABLE_DEMO_H
#define HASH_TABLE_DEMO_H
template <class Value,class Key,class HashFen,
		class ExtractKey,class EqualKey,class Alloc>
struct __hashtable_iterator_demo
{
	typedef hashtable<Value, Key, HashFen, ExtractKey, EqualKey, Alloc>
		hashtable;
	typedef __hashtable_iterator_demo<Value, Key, HashFen,
		ExtractKey, EqualKey, Alloc>
		iterator;
	typedef __hashtable_const_iterator_demo<Value, Key, HashFen,
		ExtractKey, EqualKey, Alloc>
		const_iterator;
	typedef __hashtable_node<Value> node;


	typedef forward_iterator_tag iterator_category;
	typedef Value value_type;
	typedef ptrdiff_t difference_type;
	typedef size_t size_type;
	typedef Value& reference;
	typedef Value* pointer;

	node* cur;
	hashtable* ht;

	__hashtable_iterator_demo(node* n, hashtable* tab) :cur(n), ht(tab){}
	__hashtable_iterator_demo(){}
	reference operator*()const { return cur->val; }
	pointer operator->()const { return &(operator*()); }
	iterator& operator++();
	bool operator==(const iterator& it)const { return cur == it.cur; }
	bool operator!=(const iterator& it)const { return cur != it.cur; }
};
#endif // !HASH_TABLE_DEMO_H
