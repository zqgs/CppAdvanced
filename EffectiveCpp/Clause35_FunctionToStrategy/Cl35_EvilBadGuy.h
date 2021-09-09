#pragma once
#include "Cl35_GameCharacter_Exp2.h"
class Cl35_EvilBadGuy :
	public Cl35_GameCharacter_Exp2
{
public:
	explicit Cl35_EvilBadGuy(HeadlthCalcFun hcf = Cl35_defaultHealthCalc) :
		Cl35_GameCharacter_Exp2(hcf){

	}
	~Cl35_EvilBadGuy(){}
};

