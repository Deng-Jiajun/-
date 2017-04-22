#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
class Set//集合类 数据成员为vector<int>
{
	friend Set operator+(const Set&, const Set&);//并集
	friend Set operator*(const Set&, const Set&);//交集
	friend Set operator-(const Set&, const Set&);//差
	friend bool operator==(const Set&, const Set&);//等于
public:
	Set() = default;
	Set(const std::vector<int>&);
	void Unique(void);
	void Display(void);
	int Size(void);
	~Set() = default;

private:
	std::vector<int> set_;
};
Set::Set(const std::vector<int> &copy) :set_(copy)
{
	Unique();
}
int Set::Size(void)
{
	return set_.size();
}
void Set::Unique(void)
{
	std::sort(set_.begin(), set_.end());
	auto end_unique = std::unique(set_.begin(), set_.end());
	set_.erase(end_unique, set_.end());
}
void Set::Display(void)
{
	for (const auto &i : set_)
		std::cout << i << ' ';
	std::cout << std::endl;
}
bool operator==(const Set &lhd, const Set &rhd)
{
	return (lhd.set_ == rhd.set_);
}

Set operator+(const Set &lhd, const Set &rhd)
{
	Set result = lhd.set_;
	for (auto &i : rhd.set_)
		result.set_.push_back(i);
	result.Unique();
	return result;
}
Set operator-(const Set &lhd, const Set &rhd)
{
	Set result = lhd.set_; 
	auto iter = result.set_.begin();
	
	for (int i = 0; i != result.set_.size();)
	{
		bool flag(false);
		for (auto &e : rhd.set_)
			if (result.set_[i] == e)
			{
				result.set_.erase(result.set_.begin() + i);
				flag = true;
				break;
			}
		if (!flag)
			++i;
	}
	return result;
}

Set operator*(const Set &lhd, const Set &rhd)
{
	Set result = lhd + rhd;

	result= result - ((lhd - rhd) + (rhd - lhd));
	return result;
}