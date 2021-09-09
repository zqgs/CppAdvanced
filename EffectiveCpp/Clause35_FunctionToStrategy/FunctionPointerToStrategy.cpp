// FunctionPointerToStrategy.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <functional>
#include "Cl35_EvilBadGuy.h"
#include "Cl35_EvilBadGuyExp1.h"
#include "HealthCalcFunction.h"
#include "Cl35_EvilBadGuyExp2.h"
#include "Cl35_GameCharacter_Exp4.h"
//����function
std::function<std::string(int, int)> fun1;
void testFunction()
{
	fun1 = [](int a, int b)->std::string{
		return std::to_string(a + b);
	};

	std::cout << fun1(1, 2) << std::endl;
}

//����ָ�����ģʽ
int loseHealthQuickly(const Cl35_GameCharacter_Exp2 & gc)
{
	std::cout << "loseHealthQuickly\n";
	return 15;//
}
int loseHealthSlowly(const Cl35_GameCharacter_Exp2 & gc)
{
	std::cout << "loseHealthSlowly\n";
	return -20;
}
void FuncPointerToStrategy()
{
	Cl35_EvilBadGuy ebg1(loseHealthQuickly);
	Cl35_EvilBadGuy ebg2(loseHealthSlowly);
	std::cout << ebg1.Test() << std::endl;
	std::cout << ebg2.Test() << std::endl;
}

//std::function����ģʽ
//�������㺯����ע��:�䷵��ֵ����Τnon-int
short calcHealth(const Cl35_GameCharacter_Exp3&){
	std::cout << "calcHealth function\n";
	return 30;
}

//��������
struct HealthCalculator
{
	int operator()(const Cl35_GameCharacter_Exp3&) const{
		std::cout << "HealthCalculator operator\n";
		return 40;
	}
};
void stdFuncToStrategy()
{
	Cl35_EvilBadGuyExp1 ebg_exp1(calcHealth);//����1,ʹ����ͨ�������㽡��ֵ
	std::cout <<"Cl35_EvilBadGuyExp1:healthValue:"<< ebg_exp1.healthValue()<<"\n";


	Cl35_EyeCandyCharater *ecc1 = new Cl35_EyeCandyCharater(HealthCalculator());//;//����2,ʹ�ú���������㽡��ֵ
	std::cout << "Cl35_EvilBadGuyExp1:healthValue" << ecc1->healthValue() << "\n";
	delete ecc1;

	Cl35_GameLevel currentLevel;
	Cl35_EvilBadGuyExp1 ebg_exp2(std::bind(&Cl35_GameLevel::health, currentLevel, std::placeholders::_1));//����3��ʹ��ĳ����Ա�������㽡��ֵ
	std::cout << "Cl35_EvilBadGuyExp1:healthValue:" << ebg_exp2.healthValue() << "\n";


	auto lambda = [](const Cl35_GameCharacter_Exp3& hh)->int{
		std::cout << "lambda function\n";
		return 60;
	};
	Cl35_EvilBadGuyExp1 ebg_exp4(lambda);//����4,ʹ��lambda���㽡��ֵ
	std::cout << "Cl35_EvilBadGuyExp4:healthValue:" << ebg_exp4.healthValue() << "\n";
}


void OldStrtegy()
{
	//��ͳ����ģʽ-->�Ὣ�������㺯������һ������ļ̳���ϵ�е�virtual������Ա
	Cl35_EvilBadGuyExp2 *ebg_exp2 = new Cl35_EvilBadGuyExp2();
	Cl35_GameCharacter_Exp4 ebg_exp5(ebg_exp2);
	ebg_exp5.healthValue();
	delete ebg_exp2;
}


int _tmain(int argc, _TCHAR* argv[])
{
	OldStrtegy();
	return 0;
}

