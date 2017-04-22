#ifndef STACK_H
#define STACK_H
template<typename T>
class stack
{
public:
	stack(unsigned);
	stack();
	~stack();
	void push(T);
	void pop(void);
	bool isEmpty(void);
	bool isFull(void);
	T TopValue(void);
private:
	T *sptr;
	unsigned size;
	int Top;
};

#endif // !STACK_H

