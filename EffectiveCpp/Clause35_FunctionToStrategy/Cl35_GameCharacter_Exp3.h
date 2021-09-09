#pragma once
#include <string>
#include <functional>
//����35:����std::function �Ĳ���ģʽ

class Cl35_GameCharacter_Exp3;
int Cl35_defaultHealthCalc_Exp3(const Cl35_GameCharacter_Exp3& gc);


class Cl35_GameCharacter_Exp3
{
public:
	typedef std::function<int(const Cl35_GameCharacter_Exp3&)> HealthCalcFunc;
	explicit Cl35_GameCharacter_Exp3(HealthCalcFunc hcf = Cl35_defaultHealthCalc_Exp3):
		healthCalcFunc(hcf)
	{

	}
	int healthValue() const{ return healthCalcFunc(*this);}
	~Cl35_GameCharacter_Exp3(){}

private:
	HealthCalcFunc healthCalcFunc;
};
