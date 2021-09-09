//
// Created by Sea on 2021/9/2.
//

#ifndef EFFECTIVECPP_CLAUSE35_CONSIDER_ALTERNATIVES_TO_VIRTUAL_FUNCTION_HPP
#define EFFECTIVECPP_CLAUSE35_CONSIDER_ALTERNATIVES_TO_VIRTUAL_FUNCTION_HPP

#include <functional>

//条款35:考虑virtual函数以外的其他选择

//例子1:考虑一个游戏计算人物健康指数的设计
class Cl35_GameCharacter{
public:
    virtual int healthValue() const;//不是 prue virtual,它将带有缺省实现
    virtual ~Cl35_GameCharacter()= 0;

    //这样的设计是合理的，但从某个角度说却反而成了它的弱点。是否有其他方案来代替virtual的设计方式呢？
};

//例子2:由Non-Virtual Interface手法实现Template Method模式(与C++template并无关联)
class Cl35_GameCharacter_exp1{
public:
    int healthValue() const//该non-virtual称为virtual的外覆器(wrapper)
    {
        //做一些事前工作:锁定互斥器、制造运转记录、验证class约束调教、验证函数的先决条件等
        int retVal = doHealthValue();//真正需要做的事
        //做一些事后工作:解除互斥器、验证函数的事后条件、再次验证class的约束条件
        return retVal;
    }

private:
    virtual int doHealthValue() const{

    }
};
/*
 * 把virtual设计到private中，派生类会重新定义若干个并不调用的函数。
 * 1.重新定义virtual函数表示某些事"如何"完成
 * 2.调用virtual函数表示它"何时"被完成,从而赋予它们"如何实现机能"的控制能力，但base class保留了"函数何时被调用"的权利
*/

//例子3:由Function Pointers实现Strategy模式
//详情:请看项目Clause35_FunctionToStrategy——Cl35_GameCharacter_Exp2。


//例子4:由std::Function 实现 Strategy模式
//一旦习惯了template以及它们对隐式接口的使用，基于函数指针的做法看起来显得过分苛刻与死板。
//详情:请看项目Clause35_FunctionToStrategy——Cl35_GameCharacter_Exp3。
class Cl35_GameCharacter_Exp3;
typedef std::function<int(const Cl35_GameCharacter_Exp3&)> HealthCalcFunc;
// std::function类型产生的对象可以持有任何与此签名式兼容的可调用物。
// 说人话就是:返回值能被隐式转换成int,参数能被隐式转换成const Cl35_GameCharacter_Exp3&的函数都能被std::function调用。
// 相比之下，并没有函数指针那么严苛,对于例子3的外部没有影响,但是指定的策略函数产生了惊人的弹性。


/*
总结:
1.函数指针限制比较死,只能声明一个规定格式的函数(类似callback回调函数),且返回值固定不可改变。(例3)
2.使用std::function可以兼容:普通函数、函数对象、某个成员函数、lambda表达式,且返回值支持隐式转换(例4)

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
*/

//古典的Strategy模式:传统的Strategy做法会将健康计算函数做成一个分离的继承体系中的virtual函数成员
//例子5:传统策略模式实现:请看项目Clause35_FunctionToStrategy——Cl35_GameCharacter_Exp4与健康值计算抽象类HealthCalcFunction。
class Cl35_GameCharacter_Exp4;
class HealthCalcFunction{
public:
    virtual int calc(const Cl35_GameCharacter_Exp4&)const{
        return 0;
    }
};
HealthCalcFunction defaultHealthCalc;
class Cl35_GameCharacter_Exp4
{
public:
    explicit Cl35_GameCharacter_Exp4(HealthCalcFunction *phcf = &defaultHealthCalc):
            pHealthCalc(phcf)
    {

    }
    int healthValue()const{ return pHealthCalc->calc(*this); }
    ~Cl35_GameCharacter_Exp4(){}

private:
    HealthCalcFunction* pHealthCalc;
};
//例5的好处:标准的Strategy容易辨别，而且还提供一个"既有健康算法纳入使用"的可能性----只需要为HealthCalcFunction提供一个派生类即可

/*摘要:当我们试图寻找替代虚函数的替代方法时，不妨考虑一下替代方案:
 * 1.使用non-virtual-interface(NVI)手法,那是Template Method设计模式的一种特殊形式。它以public non-virtual成员函数包裹性较低访问
 *private或protected的virtual函数。
 * 2.将virtual替换为"函数指针成员变量",这是Strategy设计模式的一种分解表现形式。
 * 3.以std::function成员变量替换virtual函数，因为允许任何可调用物(callable entity)搭配一个兼容需求的签名式。这也是Strategy设计模式的
 *一种分解形式。
 * 4.将继承体系内的virtual函数替换为另一个体系内的virtual函数。这是传统Strategy设计模式实现手法
 */

/*重点记住:
 *  1.virtual函数的替代方案包括NVI手法及Strategy设计模式的多种形式。NVI手法自身是一个特殊形式的Template Method设计模式
 *  2.将机能从成员函数转移到class外部函数，带来的一个缺点是，非成员函数无法访问class的non-public成员。
 *  3.std::function对象行为就像一般的函数指针。这样的对象可接纳"与给定的目标签名式(类似callback声明式<返回值、参数>)兼容"的所有可
 * 调用物(类似callback函数)。比如:普通函数、函数对象、某个成员函数、lambda表达式
 */



#endif //EFFECTIVECPP_CLAUSE35_CONSIDER_ALTERNATIVES_TO_VIRTUAL_FUNCTION_HPP
