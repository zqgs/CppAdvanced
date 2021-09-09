#pragma once

#include <string>
#include <memory>

class Cl31_PersonImpl;

class Cl31_PersonExp2{
public:
	Cl31_PersonExp2(const std::string &Name);
	~Cl31_PersonExp2();
	std::string name() const;
private:
	std::shared_ptr<Cl31_PersonImpl> pImpl;
};

