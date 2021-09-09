// Clause31_pImpl.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Cl31_PersonExp2.h"
#include <iostream>
int _tmain(int argc, _TCHAR* argv[])
{
	Cl31_PersonExp2 cl31("zqg");
	std::cout << cl31.name()<<"\n";
	system("pause");
	return 0;
}

