#include<string>
#include<iostream>
#include"LargeNumber.h"


const LargeNumber ZERO;
LargeNumber::LargeNumber(const std::string &num) : number_(num) {  }
LargeNumber::LargeNumber(const LargeNumber &Largenum) : number_(Largenum.number_) {  }
LargeNumber abs(const LargeNumber &num)
{
	LargeNumber result(num);
	if (result < ZERO)
		result.number_.erase(result.number_.begin());
	return result;
}
LargeNumber& LargeNumber::operator-(void)
{
	number_.insert(number_.begin(), '-');
	return *this;
}
LargeNumber LargeNumber::CutZero(void)
{
	std::string::iterator ite = (*number_.begin() == '-') ? number_.begin() + 1 : number_.begin(), b = ite;

	while (ite != number_.end() - 1 && *ite == '0') ++ite;
	number_.erase(b, ite);
	//ȥ��ǰ��0�󣬽��Ϊ-0,��ֵ��Ϊ0
	if (number() == "-0") number_ = "0";
	return *this;
}

std::ostream& operator<<(std::ostream &os, const LargeNumber &num)
{
	os << num.number_;
	return os;
}
std::istream& operator>>(std::istream &is, LargeNumber &num)
{

	if (is >> num.number_)
	{
		//���޴��󣬴���ǰ��0
		num.CutZero();
	}
	else
		num = LargeNumber();//��������ֵתΪ0
	return is;
}
bool operator<(const LargeNumber &lhs, const LargeNumber &rhs)
{
	LargeNumber left_side(lhs), right_side(rhs);
	left_side.CutZero(); right_side.CutZero();

	if (left_side == right_side) return false;

	if (left_side.number().at(0) == '-' && right_side.number().at(0) != '-') return true;
	if (left_side.number().at(0) != '-' && right_side.number().at(0) == '-') return false;

	if (left_side.number().at(0) != '-' && right_side.number().at(0) != '-')
	{
		if (left_side.number().size() < right_side.number().size()) return true;
		if (left_side.number().size() > right_side.number().size()) return false;

		if (left_side.number().size() == right_side.number().size())
		{
			if (left_side.number() < right_side.number())return true;
			if (left_side.number() > right_side.number())return false;
		}
	}

	if (left_side.number().at(0) == '-' && right_side.number().at(0) == '-')
	{

		/*left_side.number_.erase(left_side.number_.begin());
		right_side.number_.erase(right_side.number_.begin());*/

		left_side = abs(left_side); right_side = abs(right_side);

		/*
		if (left_side.number().size() < right_side.number().size()) return false;
		if (left_side.number().size() > right_side.number().size()) return true;

		if (left_side.number().size() == right_side.number().size())
		{
			if (left_side.number() < right_side.number())return false;
			if (left_side.number() > right_side.number())return true;
		}
		*/

		return !(left_side < right_side);
	}
}
bool operator<=(const LargeNumber &lhs, const LargeNumber &rhs)
{
	return (lhs < rhs || lhs == rhs);
}
bool operator>(const LargeNumber &lhs, const LargeNumber &rhs)
{
	if (lhs == rhs) return false;//��ȷ���false,�� �·� lhs<rhs �ıȽ��в����� lhs==rhs �Ŀ���
	return !(lhs < rhs);
}
bool operator>=(const LargeNumber &lhs, const LargeNumber &rhs)
{
	return (lhs > rhs || lhs == rhs);
}
bool operator==(const LargeNumber &lhs, const LargeNumber &rhs)
{
	LargeNumber left_side(lhs), right_side(rhs);
	left_side.CutZero(); right_side.CutZero();
	return (left_side.number() == right_side.number());
}
bool operator!=(const LargeNumber &lhs, const LargeNumber &rhs)
{
	return !(lhs == rhs);
}

LargeNumber operator+(const LargeNumber &lhs, const LargeNumber &rhs)
{
	LargeNumber left_side(lhs), right_side(rhs);
	left_side.CutZero(); right_side.CutZero();
	//0ֵ�ж�
	if (left_side == ZERO && right_side == ZERO) return ZERO;
	if ((left_side == ZERO && right_side != ZERO) || (left_side != ZERO && right_side == ZERO))
	{
		return left_side != ZERO ? left_side : right_side;
	}

	if (left_side < right_side) swap(left_side.number_, right_side.number_);//��������

	//��+��
	if (left_side > ZERO && right_side > ZERO)
	{

		std::string::iterator  left_beg(left_side.number_.begin());
		std::string::iterator  left_ite(left_side.number_.end());
		std::string::iterator right_beg(right_side.number_.begin());
		std::string::iterator right_ite(right_side.number_.end());
		bool carry = false;//��λ

		while (left_ite != left_beg)
		{
			int tmp;
			if (right_ite != right_beg)
				tmp = *(--left_ite) + *(--right_ite) + carry - '0';
			else
				tmp = *(--left_ite) + carry;

			carry = false;//��λ��ʹ��

			if (tmp > '9')
			{
				tmp -= 10;
				carry = true;
			}
			*left_ite = tmp;
		}

		if (carry) left_side.number_.insert(left_beg, '1');
		return left_side;
	}

	//��+��
	if (left_side > ZERO && right_side < ZERO)
	{
		////ȥ���ţ�������
		////right_side.number_.erase(right_side.number_.begin());
		//right_side = abs(right_side);
		//return left_side - right_side;
		return left_side - abs(right_side);
	}

	//��+�� <=> -(��+��)
	if (left_side < ZERO && right_side < ZERO)
	{
		////left_side.number_.erase(left_side.number_.begin());
		//left_side = abs(left_side);
		////right_side.number_.erase(right_side.number_.begin());
		//right_side = abs(right_side);

		///*left_side += right_side;
		//left_side.number_.insert(left_side.number_.begin(), '-');
		//return left_side;*/
		//return -(left_side + right_side);
		return -(abs(left_side) + abs(right_side));
	}
	return ZERO;
}

LargeNumber& LargeNumber::operator+=(const LargeNumber &rhs)
{
	*this = *this + rhs;
	return *this;
}

LargeNumber& LargeNumber::operator++(void)
{
	*this += LargeNumber("1");
	return *this;
}
LargeNumber LargeNumber::operator++(int)
{
	LargeNumber result = *this;
	*this += LargeNumber("1");
	return result;
}
LargeNumber operator-(const LargeNumber &lhs, const LargeNumber &rhs)
{
	LargeNumber left_side(lhs), right_side(rhs);
	left_side.CutZero(); right_side.CutZero();
	//0ֵ�ж�
	if (left_side != ZERO && right_side == ZERO) return left_side;
	if (left_side == ZERO && right_side != ZERO)
	{
		//if (right_side > ZERO)
		//	//right_side.number_.insert(right_side.number_.begin(), '-');
		//	right_side = -right_side;
		//else
		//	//right_side.number_.erase(right_side.number_.begin());
		//	right_side = abs(right_side);
		//return right_side;

		return (right_side > ZERO) ? -right_side : abs(right_side);
	}



	//�����ֵ���
	if (left_side == right_side) return ZERO;
	//��-��
	if (left_side > ZERO && right_side > ZERO)
	{
		bool flag(false);
		if (left_side < right_side)
		{
			swap(left_side.number_, right_side.number_);//��������
			flag = true;//���ű��
		}
		std::string::iterator  left_beg(left_side.number_.begin());
		std::string::iterator  left_ite(left_side.number_.end());
		std::string::iterator right_beg(right_side.number_.begin());
		std::string::iterator right_ite(right_side.number_.end());
		bool back = false;//��λ

		while (left_ite != left_beg)
		{
			int tmp;
			if (right_ite != right_beg)
				tmp = *(--left_ite) - *(--right_ite) - back + '0';
			else
				tmp = *(--left_ite) - back;
			back = false;//��λ��ʹ��

			if (tmp < '0')
			{
				tmp += 10;
				back = true;
			}
			*left_ite = tmp;
		}

		left_side.CutZero();

		//if (flag)//������
		//	left_side = -left_side;
		//	//left_side.number_.insert(left_beg, '-');
		//return left_side;
		return flag ? -left_side : left_side;
	}

	//��-��
	if (left_side < ZERO && right_side < ZERO)
	{
		////ȥ����
		///*left_side.number_.erase(left_side.number_.begin());
		//right_side.number_.erase(right_side.number_.begin());*/
		//left_side = abs(left_side);
		//right_side = abs(right_side);
		////��-�Ҹ� <=> ����-����
		//return right_side - left_side;

		return abs(right_side) - abs(left_side);
	}

	//��-��
	if (left_side > ZERO && right_side < ZERO)
	{
		//right_side.number_.erase(right_side.number_.begin());

		/*right_side = abs(right_side);
		return left_side + right_side;*/
		return left_side + abs(right_side);
	}
	//��-�� <=> ��+��
	if (left_side < ZERO && right_side > ZERO)
	{
		//right_side.number_.insert(right_side.number_.begin(), '-');
		return left_side + -right_side;
	}
	return ZERO;
}

LargeNumber& LargeNumber::operator-=(const LargeNumber &rhs)
{
	*this = *this - rhs;
	return *this;
}
LargeNumber& LargeNumber::operator--(void)
{
	*this -= LargeNumber("1");
	return *this;
}
LargeNumber LargeNumber::operator--(int)
{
	LargeNumber result = *this;
	*this -= LargeNumber("1");
	return result;
}
LargeNumber operator*(const LargeNumber &lhs, const LargeNumber &rhs)
{
	LargeNumber left_side(lhs), right_side(rhs);
	left_side.CutZero(); right_side.CutZero();

	//0ֵ
	if (left_side == ZERO || right_side == ZERO) return ZERO;

	if (left_side < right_side)
		swap(left_side.number_, right_side.number_);//��������

	//��*��
	if (left_side > ZERO && right_side > ZERO)
	{
		if (right_side.number_.size() == 1)
		{
			LargeNumber result(ZERO);
			int count = right_side.number_.at(0) - '0';
			while (count--)
				result += left_side;
			return result;
		}
		else
		{
			LargeNumber result(ZERO), tmp(ZERO);
			std::string::iterator right_beg(right_side.number_.begin());
			std::string::iterator right_ite(right_side.number_.end());
			std::string zero;
			while (right_ite != right_beg)
			{
				tmp.number_ = *--right_ite;
				tmp *= left_side;
				tmp.number_ += zero;
				result += tmp;
				zero += '0';
			}
			return result;
		}
	}
	//��*�� ȥ���ţ���*����������
	if (left_side > ZERO && right_side < ZERO)
	{
		////right_side.number_.erase(right_side.number_.begin());
		////LargeNumber result = left_side*right_side;
		//LargeNumber result = left_side*abs(right_side);
		//result.number_.insert(result.number_.begin(), '-');
		//return result;
		return -(left_side*abs(right_side));
	}
	//��*�� ȥ���ţ���*��
	if (left_side < ZERO && right_side < ZERO)
	{
		/*	left_side.number_.erase(left_side.number_.begin());
			right_side.number_.erase(right_side.number_.begin());
			return left_side*right_side;*/
		return abs(left_side)*abs(right_side);
	}
	return ZERO;
}
LargeNumber& LargeNumber::operator*=(const LargeNumber &rhs)
{
	*this = *this * rhs;
	return *this;
}
LargeNumber operator/(const LargeNumber &lhs, const LargeNumber &rhs)
{
	LargeNumber left_side(lhs), right_side(rhs);
	left_side.CutZero(); right_side.CutZero();

	//0ֵ
	if (left_side == ZERO || right_side == ZERO) return ZERO;

	//��ȣ�ֵΪ1
	if (left_side == right_side) return LargeNumber("1");

	//������ģС�ڱ�������ģ
	if (abs(left_side) < abs(right_side))
	{
		return ZERO;
	}
	//��/��
	if (left_side > ZERO && right_side > ZERO)
	{
		LargeNumber result(ZERO);
		int digit_difference = left_side.number_.size() - right_side.number_.size();
		right_side.number_.insert(right_side.number_.end(), digit_difference, '0');//��0����
		while (left_side > ZERO && digit_difference >= 0)
		{
			LargeNumber tmp("0");
			while (left_side >= right_side)
			{
				left_side -= right_side;
				++tmp;
			}
			tmp.number_.insert(tmp.number_.end(), digit_difference, '0');
			result += tmp;
			--digit_difference;
			right_side.number_.erase(right_side.number_.end() - 1);
		}
		return result;
	}
	//��/��||��/��
	if ((left_side<ZERO&&right_side>ZERO) || (left_side > ZERO&&right_side < ZERO))
	{
		return -(abs(left_side) / abs(right_side));
	}
	//��/��
	if (left_side < ZERO && right_side < ZERO)
	{
		return abs(left_side) / abs(right_side);
	}
	return ZERO;
}
LargeNumber& LargeNumber::operator/=(const LargeNumber &rhs)
{
	*this = *this / rhs;
	return *this;
}