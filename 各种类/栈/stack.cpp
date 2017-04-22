#include"stack.h"
#include<iostream>
template<typename T>
stack<T>::stack() :stack(10) {};
template<typename T>
stack<T>::stack(unsigned n) : size(n), Top(-1)
{
	sptr = new T[size];
}
template<typename T>
stack<T>::~stack()
{
	delete sptr;
}
template<typename T>
void stack<T>::push(T element)
{
	if(!isFull())
	{
		++Top;
		sptr[Top] = element;
	}
	else
	{
		std::cerr << "Õ»Âú£¡" << std::endl;
	}
}
template<typename T>
void stack<T>::pop(void)
{
	if (!isEmpty())
		--Top;
	else
	{
		std::cerr << "Õ»¿Õ£¡" << std::endl;
	}
}
template<typename T>
bool stack<T>::isEmpty(void)
{
	return Top == -1;
}
template<typename T>
bool stack<T>::isFull(void)
{
	return Top == size-1;
}
template<typename T>
T stack<T>::TopValue(void)
{
	return sptr[Top];
}



//²âÊÔÕ»×´Ì¬º¯Êý
template<typename T>
void StackState(stack<T> &T_stack)
{
	if (T_stack.isEmpty())cout << "¿Õ" << endl;
	if (T_stack.isFull())cout << "Âú" << endl;
}