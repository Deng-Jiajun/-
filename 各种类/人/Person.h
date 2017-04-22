#ifndef PERSON_H
#define PERSON_H
#include<iostream>
#include<string>
struct BirthDay;
class Person;
const int kperson_number=1;
struct BirthDay
{
	int year=0;
	int month=0;
	int day=0;
};
class Person
{
public:
	Person();
	Person(const Person&);
	~Person()=default;
	void InputInformation(void);
	void OutputInformation(void);
	static void FindPerson(void);
	std::string IdPerson(void) { return IdPerson_; }
	std::string Name(void) { return Name_; }
private:
	std::string IdPerson_;
	std::string Name_;
	std::string Sex_;
	std::string HomeAddress_;
	BirthDay bitrhday_;
};

Person::Person()
{
	IdPerson_ = "None";
	Name_ = "None";
	Sex_ = "None";
	HomeAddress_ = "None";
	bitrhday_ = { 0,0,0 };
}
Person::Person(const Person &copy)
{
	IdPerson_ = copy.IdPerson_;
	Name_ = copy.Name_;
	Sex_ = copy.Sex_;
	HomeAddress_ = copy.HomeAddress_;
	bitrhday_ = copy.bitrhday_;
}

void Person::InputInformation(void)
{
	std::cout << "Please Enter the information." << std::endl;
	std::cout << "ID: "; std::cin >> IdPerson_;
	std::cout << "Name: "; std::cin>> Name_;
	std::cout << "Sex: "; std::cin >> Sex_;
	std::cout << "HomeAddress: "; std::cin>> HomeAddress_;
	std::cout << "bitrhday(year month day): "; std::cin >> bitrhday_.year >> bitrhday_.month >> bitrhday_.day;
	std::cout << "Input Done!\n" << std::endl;
}
void Person::OutputInformation(void)
{
	std::cout << "ID: " << IdPerson_ << '\n';
	std::cout << "Name: " << Name_ << '\n';
	std::cout << "Sex: " << Sex_ << '\n';
	std::cout << "HomeAddress: " << HomeAddress_ << '\n';
	std::cout << "bitrhday: " << bitrhday_.year<<'-'<< bitrhday_.month<<'-'<< bitrhday_.day <<'\n' <<std::endl;
}

Person p[kperson_number];
void Person::FindPerson(void)
{
	std::cout << "Find person, Please Input name or ID: ";
	std::string str; std::cin >> str;
	for (int i = 0; i != kperson_number; ++i)
	{
		if ((p[i].IdPerson() == str) || (p[i].Name() == str))
		{
			std::cout << "find!" << std::endl;
			p[i].OutputInformation();
			return;
		}
	}
	std::cout << "No find!" << std::endl;
}
#endif // !PERSON_H
