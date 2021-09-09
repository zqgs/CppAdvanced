// FunctionPointerToStrategy.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <functional>
#include "Cl35_EvilBadGuy.h"
#include "Cl35_EvilBadGuyExp1.h"
#include "HealthCalcFunction.h"
#include "Cl35_EvilBadGuyExp2.h"
#include "Cl35_GameCharacter_Exp4.h"
//测试function
std::function<std::string(int, int)> fun1;
void testFunction()
{
	fun1 = [](int a, int b)->std::string{
		return std::to_string(a + b);
	};

	std::cout << fun1(1, 2) << std::endl;
}

//函数指针策略模式
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

//std::function策略模式
//健康计算函数，注意:其返回值类型韦non-int
short calcHealth(const Cl35_GameCharacter_Exp3&){
	std::cout << "calcHealth function\n";
	return 30;
}

//函数对象
struct HealthCalculator
{
	int operator()(const Cl35_GameCharacter_Exp3&) const{
		std::cout << "HealthCalculator operator\n";
		return 40;
	}
};
void stdFuncToStrategy()
{
	Cl35_EvilBadGuyExp1 ebg_exp1(calcHealth);//人物1,使用普通函数计算健康值
	std::cout <<"Cl35_EvilBadGuyExp1:healthValue:"<< ebg_exp1.healthValue()<<"\n";


	Cl35_EyeCandyCharater *ecc1 = new Cl35_EyeCandyCharater(HealthCalculator());//;//人物2,使用函数对象计算健康值
	std::cout << "Cl35_EvilBadGuyExp1:healthValue" << ecc1->healthValue() << "\n";
	delete ecc1;

	Cl35_GameLevel currentLevel;
	Cl35_EvilBadGuyExp1 ebg_exp2(std::bind(&Cl35_GameLevel::health, currentLevel, std::placeholders::_1));//人物3，使用某个成员函数计算健康值
	std::cout << "Cl35_EvilBadGuyExp1:healthValue:" << ebg_exp2.healthValue() << "\n";


	auto lambda = [](const Cl35_GameCharacter_Exp3& hh)->int{
		std::cout << "lambda function\n";
		return 60;
	};
	Cl35_EvilBadGuyExp1 ebg_exp4(lambda);//人物4,使用lambda计算健康值
	std::cout << "Cl35_EvilBadGuyExp4:healthValue:" << ebg_exp4.healthValue() << "\n";
}


void OldStrtegy()
{
	//传统策略模式-->会将健康计算函数做成一个分离的继承体系中的virtual函数成员
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

