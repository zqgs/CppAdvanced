#pragma once
#include <iostream>
#include "Cl35_GameCharacter_Exp3.h"

class Cl35_GameLevel
{
public:
	float health(const Cl35_GameCharacter_Exp3&) const{
		std::cout << "Cl35_GameLevel::health\n";
		return 50.1;
	}
private:

};

//人物1
class Cl35_EvilBadGuyExp1 :
	public Cl35_GameCharacter_Exp3
{
public:
	explicit Cl35_EvilBadGuyExp1(HealthCalcFunc hcf = Cl35_defaultHealthCalc_Exp3) :
		Cl35_GameCharacter_Exp3(hcf){
	}
	~Cl35_EvilBadGuyExp1(){}
};

//人物2
class Cl35_EyeCandyCharater :
	public Cl35_GameCharacter_Exp3
{
public:
	explicit Cl35_EyeCandyCharater(HealthCalcFunc hcf = Cl35_defaultHealthCalc_Exp3) :
		Cl35_GameCharacter_Exp3(hcf){

	}
	~Cl35_EyeCandyCharater(){}
};
