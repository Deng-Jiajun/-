
#include<iostream>
#include"Complex.h"
using namespace std;

int main(void)
{
	Complex a(1, 1), b(2, 2),c;
	c = a + b;
	c.Print();
	c = a - b;
	c.Print();
	c = a * b;
	c.Print();
	c = a / b;
	c.Print();

	system("pause");
	return 0;
}