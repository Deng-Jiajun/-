#include<iostream>
#include"Set.h"
using namespace std;
int main(void)
{
	std::cout << "hello world\n";
	Set s1(vector<int>{1, 5, 6, 3, 3, 4, 7, 5, 2, 1, 9, 3, 6, 4, 2, 1});
	Set s2(vector<int>{1, 2, 3, 8,9});
	s1.Display();
	s2.Display();
	(s1 + s2).Display();
	(s1-s2).Display();
	(s1 * s2).Display();

	system("pause");
	return 0;
}
