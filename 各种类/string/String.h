#ifndef STRING_H
#define STRING_H


#include<cstring>
#include<iostream>
class String
{
public:
	String(char *Head);
	~String();
	void Reverse(void);
	void display(void);
	int size(void) { return strlen(head); }
private:
	char *head;
};
String::String(char *Head)
{
	head = new char[strlen(Head) + 1];
	strcpy(head, Head);
}
void String::display(void)
{
	std::cout << head;
}
void String::Reverse(void)
{
	for (int i = 0; i != size() / 2; ++i)
	{
		char tmp=*(head + i);
		*(head + i) = *(head + size() - 1 - i);
		*(head + size() - 1 - i) = tmp;
	}
}
String::~String()
{
	delete head;
}
#endif // !STRING_H