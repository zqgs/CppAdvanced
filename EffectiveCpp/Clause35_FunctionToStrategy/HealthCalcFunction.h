#pragma once

//传统策略模式实现

class Cl35_GameCharacter_Exp4;
class HealthCalcFunction{
public:
	virtual int calc(const Cl35_GameCharacter_Exp4&)const{
		return 0;
	}
};