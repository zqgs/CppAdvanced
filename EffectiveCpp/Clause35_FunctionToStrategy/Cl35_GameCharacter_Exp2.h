#pragma once
#include <string>
//����35:���ں���ָ��Ĳ���ģʽ

class Cl35_GameCharacter_Exp2;

int Cl35_defaultHealthCalc(const Cl35_GameCharacter_Exp2& gc);

class Cl35_GameCharacter_Exp2
{
public:
	typedef int(*HeadlthCalcFun)(const Cl35_GameCharacter_Exp2&);
	explicit Cl35_GameCharacter_Exp2(HeadlthCalcFun hcf = Cl35_defaultHealthCalc) :headlthFunc(hcf){}
	~Cl35_GameCharacter_Exp2(){}

	int Test()
	{
		return headlthFunc(*this);
	}

private:
	HeadlthCalcFun headlthFunc;
};

