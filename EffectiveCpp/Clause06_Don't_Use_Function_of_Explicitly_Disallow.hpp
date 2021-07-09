//
// Created by Sea on 2021/7/9.
//

#ifndef EFFECTIVECPP_CLAUSE06_DON_T_USE_FUNCTION_OF_EXPLICITLY_DISALLOW_HPP
#define EFFECTIVECPP_CLAUSE06_DON_T_USE_FUNCTION_OF_EXPLICITLY_DISALLOW_HPP

//条款06：若不想使用编译器自动生成的函数，就应该明确的拒绝

//例子class HomeForSale{};//该类拒绝发生拷贝
//需要阻止发生拷贝->HomeForSale h1,h2;
//HomeForSale h3(h1);//应该拒绝编译,h1=h2//也应该拒绝编译
//阻止方法一:将copy构造函数和copy拷贝赋值操作符声明为privaite并做实现。缺点:members和friend仍然能够访问
//阻止方法二:将copy构造函数和copy拷贝赋值操作符声明为privaite不做实现。缺点该声明在类本身，如果不实现无法通过编译
//阻止方法三:使用基类通过继承来禁用copy构造函数和copy拷贝赋值操作符。
//例如:
class Uncopyalbe{
protected:
    //允许派生对象构造和析构
    Uncopyalbe(){}
    ~Uncopyalbe(){}

private:
    Uncopyalbe (const Uncopyalbe&);
    Uncopyalbe& operator=(const Uncopyalbe &);
};

class HomeForSale: private Uncopyalbe{
    //不需要再声明copy构造函数和copy拷贝赋值操作符
};

#endif //EFFECTIVECPP_CLAUSE06_DON_T_USE_FUNCTION_OF_EXPLICITLY_DISALLOW_HPP
