//Rational.h
#ifndef RATIONAL_H
#define RATIONAL_H

#include<iostream>
#include<iomanip>
class Rational
{
	friend Rational operator+(const Rational&, const Rational&);
	friend Rational operator-(const Rational&, const Rational&);
	friend Rational operator*(const Rational&, const Rational&);
	friend Rational operator/(const Rational&, const Rational&);
public:
	Rational(int, int);
	Rational() :Rational(0, 0) {}
	~Rational() = default;
	void PrintInFloat(void);
	void PrintInfraction(void);

private:
	int numerator;
	int denominator;

};
int gcd(int, int);
void simplification(int&, int&);


Rational::Rational(int n, int d) :numerator(n), denominator(d)
{
	simplification(numerator, denominator);
}
//最大公约数
int gcd(int a, int b)
{
	while (a != b)
	{
		if (a > b)
			a -= b;
		else
			b -= a;
	}
	return a;
}
//化最简
void simplification(int &a, int &b)
{
	if (a != 0 && b != 0)
	{
		int tmp_a(abs(a)), tmp_b(abs(b));

		a = ((a < 0 && b>0) || (a > 0 && b < 0)) ? -tmp_a / gcd(tmp_a, tmp_b) : tmp_a / gcd(tmp_a, tmp_b);
		b = tmp_b / gcd(tmp_a, tmp_b);
	}
}
Rational operator+(const Rational &lhs, const Rational &rhs)
{
	if (lhs.denominator != 0 && rhs.denominator == 0)return lhs;
	if (lhs.denominator == 0 && rhs.denominator != 0)return rhs;
	if (lhs.denominator == 0 && rhs.denominator == 0)return Rational();

	Rational result;
	result.denominator = lhs.denominator*rhs.denominator;
	result.numerator = lhs.numerator*rhs.denominator + lhs.denominator*rhs.numerator;
	if (result.numerator == 0 || result.denominator == 0) return Rational();
	simplification(result.numerator, result.denominator);
	return result;
}

Rational operator-(const Rational &lhs, const Rational &rhs)
{
	if (lhs.denominator != 0 && rhs.denominator == 0)return lhs;
	if (lhs.denominator == 0 && rhs.denominator != 0)
	{
		Rational result = rhs;
		result.numerator = -result.numerator;
		return result;
	}
	if (lhs.denominator == 0 && rhs.denominator == 0)return Rational();

	Rational result;
	result.denominator = lhs.denominator*rhs.denominator;
	result.numerator = lhs.numerator*rhs.denominator - lhs.denominator*rhs.numerator;
	if (result.numerator == 0 || result.denominator == 0) return Rational();
	simplification(result.numerator, result.denominator);
	return result;
}
Rational operator*(const Rational &lhs, const Rational &rhs)
{
	if (lhs.numerator == 0 || rhs.numerator == 0 || lhs.denominator == 0 || rhs.denominator == 0)return Rational();

	Rational result;
	result.denominator = lhs.denominator*rhs.denominator;
	result.numerator = lhs.numerator*rhs.numerator;
	if (result.numerator == 0 || result.denominator == 0) return Rational();
	simplification(result.numerator, result.denominator);
	return result;
}

Rational operator/(const Rational &lhs, const Rational &rhs)
{
	if (lhs.numerator == 0 || rhs.numerator == 0 || lhs.denominator == 0 || rhs.denominator == 0)return Rational();

	Rational result;
	result.denominator = lhs.denominator*rhs.numerator;
	result.numerator = lhs.numerator*rhs.denominator;
	if (result.numerator == 0 || result.denominator == 0) return Rational();
	simplification(result.numerator, result.denominator);
	//if (result.denominator < 0)
	//{
	//	result.denominator *=-1;
	//	result.numerator *=-1;

	//}
	return result;
}
void Rational::PrintInfraction(void)
{
	std::cout << numerator << '/' << denominator << std::endl;
}
void Rational::PrintInFloat(void)
{
	if (numerator == 0 || denominator == 0)
		std::cout << 0 << std::endl;
	else
		std::cout << static_cast<double>(numerator) / denominator << std::endl;
}

#endif // !RATIONAL_H
