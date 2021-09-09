#pragma once
#include <string>
class Cl31_PersonImpl
{
public:
	Cl31_PersonImpl(const std::string &Name);
	~Cl31_PersonImpl();
	std::string name() const;
private:
	std::string theName;
};

