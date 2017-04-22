#pragma once
#include<iostream>
class Complex//复数类，提供加减乘除和简陋的print操作
{
	friend Complex operator+(const Complex&, const Complex&);
	friend Complex operator-(const Complex&, const Complex&);
	friend Complex operator*(const Complex&, const Complex&);
	friend Complex operator/(const Complex&, const Complex&);
public:
	Complex(double a, double b) :real_part(a), imaginary_part(b) {}
	Complex() :Complex(0, 0) {}//默认构造，委托构造
	Complex(const Complex&);//拷贝构造
	void Print(void);
private:
	double real_part;
	double imaginary_part;
};
Complex::Complex(const Complex &c)
{
	real_part = c.real_part;
	imaginary_part = c.imaginary_part;
}
void Complex::Print(void)
{
	std::cout << real_part << '+' << imaginary_part << 'i' << std::endl;
}
Complex operator+(const Complex &lhd, const Complex &rhd)
{
	//（a + bi） + （c + di） = （a + c） + （b + d）i
	return Complex(lhd.real_part + rhd.real_part, lhd.imaginary_part + rhd.imaginary_part);
}
Complex operator-(const Complex &lhd, const Complex &rhd)
{
	//（a + bi） - （c + di） = （a - c） + （b - d）i
	return Complex(lhd.real_part - rhd.real_part, lhd.imaginary_part - rhd.imaginary_part);
}

Complex operator*(const Complex &lhd, const Complex &rhd)
{
	//（a + bi）·（c + di） = （ac - bd） + （bc + ad）i
	Complex result;

	result.real_part = lhd.real_part * rhd.real_part - lhd.imaginary_part * rhd.imaginary_part;
	result.imaginary_part = lhd.imaginary_part*rhd.real_part + lhd.real_part*rhd.imaginary_part;
	return result;
}

Complex operator/(const Complex &lhd, const Complex &rhd)
{
	//（a + bi） / （c + di） = [（ac + bd） / （c² + d²）] + [（bc - ad） / （c² + d²）]i
	Complex result;
	result.real_part = (lhd.real_part * rhd.real_part + lhd.imaginary_part * rhd.imaginary_part) / (pow(rhd.real_part, 2) + pow(rhd.imaginary_part, 2));
	result.imaginary_part = (lhd.imaginary_part*rhd.real_part - lhd.real_part*rhd.imaginary_part) / (pow(rhd.real_part, 2) + pow(rhd.imaginary_part, 2));
	return result;
}
