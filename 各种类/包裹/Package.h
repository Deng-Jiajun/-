#ifndef PACKAGE_H
#define PACKAGE_H
#include<iostream>
#include<string>
class Information
{
public:
	Information() = default;
	Information(const std::string &, const std::string &, const std::string &, const std::string &, const std::string &);
	void PrintInfomation(std::ostream&)const;
	~Information() = default;

private:
	std::string name_;
	std::string address_;
	std::string city_;
	std::string state_;
	std::string postcode_;
};
Information::Information(const std::string &name, const std::string &address, const std::string &city, const std::string &state, const std::string &postcod) :name_(name), address_(address), city_(city), state_(state), postcode_(postcod) {}
void Information::PrintInfomation(std::ostream &os)const
{
	os << "name: " << name_ << '\n'
		<< "address: " << address_ << '\n'
		<< "city: " << city_ << '\n'
		<< "state: " << state_ << '\n'
		<< "postcode: " << postcode_ << std::endl;
}

class Package
{
	friend class Information;
public:
	Package() = default;
	Package(const Information&, const Information&, double, double);
	void PrintPersonInformation(std::ostream&);
	virtual double CalculateCost(void);
	virtual void PrintPackagInformation(std::ostream&);
	virtual ~Package() = default;
private:
	Information sender_;
	Information receiver_;
protected:
	double package_weight_ounce_;
	double per_ounce_cost_;
};
Package::Package(const Information &sender, const Information &receiver, double weight, double per_cost) :sender_(sender), receiver_(receiver), package_weight_ounce_(weight), per_ounce_cost_(per_cost) {}
void Package::PrintPersonInformation(std::ostream &os)
{
	os << "sender:" << std::endl;
	sender_.PrintInfomation(os);
	os << std::endl;
	os << "receiver:" << std::endl;
	receiver_.PrintInfomation(os);
}
double Package::CalculateCost(void)
{
	return package_weight_ounce_*per_ounce_cost_;
}
void Package::PrintPackagInformation(std::ostream &os)
{
	os << "Package weight by ounce: " << package_weight_ounce_ << '\n'
		<< "per ounce cost: " << per_ounce_cost_ << '\n'
		<< "Total cost: " << CalculateCost() << std::endl;
}


class TwoDayPackage :public Package
{
public:
	TwoDayPackage() = default;
	TwoDayPackage(const Information&, const Information&, double, double, double);
	virtual double CalculateCost(void)override;
	void PrintPackagInformation(std::ostream&)override;
	virtual ~TwoDayPackage()override = default;

private:
	double twoday_service_fee;
};
TwoDayPackage::TwoDayPackage(const Information &sender, const Information &receiver, double weight, double per_cost, double service_fee) :Package(sender, receiver, weight, per_cost), twoday_service_fee(service_fee) {}

double TwoDayPackage::CalculateCost(void)
{
	return Package::CalculateCost() + twoday_service_fee;
}
void TwoDayPackage::PrintPackagInformation(std::ostream &os)
{
	os << "Package weight by ounce: " << package_weight_ounce_ << '\n'
		<< "per ounce cost: " << per_ounce_cost_ << '\n'
		<< "Twoday Package service fee: " << twoday_service_fee << '\n'
		<< "Total cost: " << CalculateCost() << std::endl;
}


class OvernightPackage :public Package
{
public:
	OvernightPackage() = default;
	OvernightPackage(const Information&, const Information&, double, double, double);
	virtual double CalculateCost(void)override;
	void PrintPackagInformation(std::ostream &os)override;
	virtual ~OvernightPackage()override = default;
private:
	double per_ounce_service_fee;
};
OvernightPackage::OvernightPackage(const Information &sender, const Information &receiver, double weight, double per_cost, double per_ounce_fee) :Package(sender, receiver, weight, per_cost), per_ounce_service_fee(per_ounce_fee) {}

double OvernightPackage::CalculateCost(void)
{
	per_ounce_cost_ += per_ounce_service_fee;
	return Package::CalculateCost();
}
void OvernightPackage::PrintPackagInformation(std::ostream &os)
{
	os << "Package weight by ounce: " << package_weight_ounce_ << '\n'
		<< "Per ounce service fee: " << per_ounce_service_fee << '\n'
		<< "per ounce cost(included service fee): " << per_ounce_cost_ << '\n'
		<< "Total cost: " << CalculateCost() << std::endl;
}


void PrintTotal(std::ostream &os, Package &package)
{
	package.PrintPersonInformation(os);
	os << std::endl;
	package.PrintPackagInformation(os);
}
#endif // !PACKAGE_H

