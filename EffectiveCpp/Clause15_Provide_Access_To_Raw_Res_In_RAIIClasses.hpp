//
// Created by Sea on 2021/7/16.
//

#ifndef EFFECTIVECPP_CLAUSE15_PROVIDE_ACCESS_TO_RAW_RES_IN_RAIICLASSES_HPP
#define EFFECTIVECPP_CLAUSE15_PROVIDE_ACCESS_TO_RAW_RES_IN_RAIICLASSES_HPP

#include <memory>
#include <iostream>
//条款15:再资源管理类中提供对原始资源的访问

//通过智能指针访问底层原始(Raw)资源，智能指针均提供get()方法<显示转换>获取底层原始资源
class C14_Investment{
public:
    void Print() const{std::cout<<"C14_Investment::Print:hello\n";}
};
C14_Investment *CreateInvestment(){
    return new C14_Investment();
}
void Call_C14_Investment_DayHeld(const C14_Investment* pi){
    pi->Print();
}
void Call_C14_Investment(){
    std::shared_ptr<C14_Investment> pInv(CreateInvestment());
    //get()显示转换获取底层原始资源
    Call_C14_Investment_DayHeld(pInv.get());
}

//隐式转换获取底层资源重载<operator->和operator*>
class C14_InvestmentExp1{
public:
    bool isTaxFree() const{std::cout<<"C14_InvestmentExp1::isTaxFree:true\n";return true;}
};

C14_InvestmentExp1 *CreateInvestmentExp1(){
    return new C14_InvestmentExp1();
}
void Call_C14_InvestmentExp1(){
    std::shared_ptr<C14_InvestmentExp1> pInv(CreateInvestmentExp1());
    bool taxAblel = !(pInv->isTaxFree());//经由operator->访问资源

    std::auto_ptr<C14_InvestmentExp1> pInv2(CreateInvestmentExp1());
    bool taxAblel2 = !((*pInv2).isTaxFree());//经由operator*访问资源
}

/*使用情况:是否该提供一个显示的转换函数(例如:get成员函数)将RAII class转换为其底部资源，或是应该提供隐式转换，
 *答案主要取决于被执行的特定工作，以及使用情况。最佳设计应该是坚持条款18:"让接口容易被正确的使用，不易被误用。"
 */


/*重点记住:
 * 1.APIs往往要求访问原始资源(raw resources),所以每一个RAII class应该提供一个"取得其所管理的资源"的办法。
 * 2.对原始资源的访问可能经由显示转换或隐式转换。一般而言显示转换比较安全，但隐式转换对客户比较方便。
 */



#endif //EFFECTIVECPP_CLAUSE15_PROVIDE_ACCESS_TO_RAW_RES_IN_RAIICLASSES_HPP
