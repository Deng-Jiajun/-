#ifndef BANK_H
#define BANK_H
#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<Windows.h>
#include<iomanip>
SYSTEMTIME st;
class bank;
class bank
{
public:
	bank() :number("NULL"), rest(0), succeedtimes(0) {}
	bank(const std::string &num, const double &re) :number(num), rest(re), succeedtimes(0) {}
	void bankin(void);
	void bankout(void);
	void disp(void);
	void UserInterface(void);
private:
	std::string number;
	double rest;
	std::vector<std::string> records;
	unsigned succeedtimes;
};
void bank::bankin(void)
{
	std::cout << "Save how much money?";
	double tmp;
	std::cin >> tmp;
	rest += tmp;
	
	GetLocalTime(&st);
	std::ostringstream os;
	os << st.wYear << "-" << st.wMonth << "-" << st.wDay << "-" << "( " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << ")" << "  -save : " << tmp << "  -balance : " << rest;
	std::cout << std::fixed << std::setprecision(2);//设置输出精度，小数点后2位
	std::cout <<"Save succeed! balance : " << rest << std::endl;
	records.push_back(os.str());
	++succeedtimes;
	std::cout << std::fixed << std::setprecision(6);//恢复默认精度，小数点后6位
}

void bank::bankout(void)
{
	std::cout << "Withdraw how much money?";
	double tmp;
	std::cin >> tmp;
	rest -= tmp;
	while (rest < 0)
	{
		rest += tmp;
		std::cout << "Enter wrong,input again?(y/n)";
		char flag; 
		std::cin >> flag;
		if (flag == 'y' || flag == 'Y')
		{
			std::cout << "Withdraw how much money?";
			std::cin >> tmp;
			rest -= tmp;
		}
		else
			return;
	}
	GetLocalTime(&st);
	std::ostringstream os;
	os << st.wYear << "-" << st.wMonth << "-" << st.wDay << "-" << "( " << st.wHour << ":" << st.wMinute << ":" << st.wSecond << ")" << "  -withdraw : " << tmp << "  -balance : " << rest;
std::cout << std::fixed << std::setprecision(2);
	std::cout << "Withdraw succeed! balance : "<<rest << std::endl;
	records.push_back(os.str());
	++succeedtimes;
	std::cout << std::fixed << std::setprecision(6);
}
void bank::disp(void)
{
	std::cout << std::fixed << std::setprecision(2);
	for (const auto &s : records)
		std::cout << s << std::endl;
	std::cout << "succeedtimes :" << succeedtimes <<
		"balance : "<<rest<<'\n'<<std::endl;
	std::cout << std::fixed << std::setprecision(6);
}

void bank::UserInterface(void)
{
	unsigned sign(5);
	while (sign != 0)
	{
		std::cout << "chose operate (1---save,2---draw back,3---skim records, 0---quit)" << std::ends;
		std::cin >> sign;
		if (sign == 0)break;
		if (sign == 1)bankin();
		if (sign == 2)bankout();
		if (sign == 3)disp();
	}
}
#endif // !BANK_H
