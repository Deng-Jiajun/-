#ifndef LARGENUMBER_H
#define LARGENUMBER_H

//����,ֻ����ֵ�и��ţ���֧������
class LargeNumber
{
	friend std::ostream& operator<<(std::ostream&, const LargeNumber&);
	friend std::istream& operator>>(std::istream&, LargeNumber&);

	friend bool operator<(const LargeNumber&, const LargeNumber&);
	friend bool operator<=(const LargeNumber&, const LargeNumber&);
	friend bool operator>(const LargeNumber&, const LargeNumber&);
	friend bool operator>=(const LargeNumber&, const LargeNumber&);
	friend bool operator==(const LargeNumber&, const LargeNumber&);
	friend bool operator!=(const LargeNumber&, const LargeNumber&);

	friend LargeNumber abs(const LargeNumber&);
	friend LargeNumber operator+(const LargeNumber&, const LargeNumber&);
	friend LargeNumber operator-(const LargeNumber&, const LargeNumber&);
	friend LargeNumber operator*(const LargeNumber&, const LargeNumber&);
	//�������γ�������������,�����򱻳���Ϊ0������Ϊ0
	friend LargeNumber operator/(const LargeNumber&, const LargeNumber&);
public:
	LargeNumber() :number_("0") { }
	LargeNumber(const std::string &);
	LargeNumber(const LargeNumber &);
	~LargeNumber() = default;
	//ȥ��ǰ��0����ֵΪ��-00000��ʱ��ֵΪ0
	LargeNumber CutZero(void);
	const std::string number(void) { return number_; }
	LargeNumber& operator-(void);
	LargeNumber& operator+=(const LargeNumber&);
	LargeNumber& operator-=(const LargeNumber&);
	LargeNumber& operator*=(const LargeNumber&);
	LargeNumber& operator/=(const LargeNumber&);
	LargeNumber& operator++(void);
	LargeNumber  operator++(int);
	LargeNumber& operator--(void);
	LargeNumber  operator--(int);
private:
	std::string number_;
};

#endif // !LARGENUMBER_H
