#pragma once
#include "HealthCalcFunction.h"
//��ͳ����ģʽʵ��
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

