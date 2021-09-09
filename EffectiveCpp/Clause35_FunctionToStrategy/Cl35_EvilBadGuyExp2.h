#pragma once

#include "HealthCalcFunction.h"

//»ÀŒÔ1
class Cl35_EvilBadGuyExp2 :
	public HealthCalcFunction
{
public:
	Cl35_EvilBadGuyExp2()
	{

	}
	~Cl35_EvilBadGuyExp2(){}

	 int calc(const Cl35_GameCharacter_Exp4&)const override
	 {
		 std::cout << "Cl35_EvilBadGuyExp2 public HealthCalcFunction\n";
		return 60;
	 }
};