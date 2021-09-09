#pragma once
#include "HealthCalcFunction.h"
//传统策略模式实现
//HealthCalcFunction defaultHealthCalc;
class Cl35_GameCharacter_Exp4
{
public:
	explicit Cl35_GameCharacter_Exp4(HealthCalcFunction *phcf):
		pHealthCalc(phcf)
	{

	}
	int healthValue()const{ return pHealthCalc->calc(*this); }
	~Cl35_GameCharacter_Exp4(){}

private:
	HealthCalcFunction* pHealthCalc;
};

