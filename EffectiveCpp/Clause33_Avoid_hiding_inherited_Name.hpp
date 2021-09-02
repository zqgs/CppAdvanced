//
// Created by Sea on 2021/9/1.
//

#ifndef EFFECTIVECPP_CLAUSE33_AVOID_HIDING_INHERITED_NAME_HPP
#define EFFECTIVECPP_CLAUSE33_AVOID_HIDING_INHERITED_NAME_HPP

#include <iostream>
//条款33:便面遮掩继承而来的名称


//例子1:作用域(内层遮掩外层)
int cl33_x;//全局变量(作用域外)
void Cl33_someFunc(){
    double cl33_x;//局部变量(作用域内),内层名称会遮掩外层名称
    std::cin>>cl33_x;
}
/*---------------------------------------
 *|全局作用域  int cl33_x               |
 *|                   ______________  |
 *|                  |Cl33_someFunc    |
 *|                  |     double cl33_x |
 *----------------------------------------
 */

//例子2:导入继承之后的作用域变化
class Cl33_Base{
private:
    int x;
public:
    virtual void mf1() =0;
    virtual void mf2(){std::cout<<"Cl33_Base::mf2\n";}
    void mf3(){std::cout<<"Cl33_Base::mf3\n";}
};
class Cl33_Derived:
        public Cl33_Base{
public:
    virtual void mf1(){std::cout<<"Cl33_Derived::mf1\n";}
    void mf4(){mf2();}
};

void Cl33_test01()
{
    Cl33_Derived cl33d;
    cl33d.mf1();
    cl33d.mf3();
    cl33d.mf4();
}
//编译器名称查找规则:首先查找其外围作用域,就是class Derived覆盖的作用域。如果没找到就继续往外移动查找，本例种的class Base。
//如果还找不到，则搜索Base的namespace作用域，最后查找全局作用域


//例子3:
class Cl33_BaseExp1{
private:
    int x;
public:
    virtual void mf1() =0;
    virtual void mf1(int ){std::cout<<"Cl33_BaseExp1::mf1(int)\n";}
    virtual void mf2(){std::cout<<"Cl33_BaseExp1::mf2\n";}
    void mf3(){std::cout<<"Cl33_BaseExp1::mf3\n";}
    void mf3(double ){std::cout<<"Cl33_BaseExp1::mf3(int)\n";}
};
class Cl33_DerivedExp1:
        public Cl33_BaseExp1{
public:
    virtual void mf1(){std::cout<<"Cl33_DerivedExp1::mf1\n";}
    void mf3(){std::cout<<"Cl33_DerivedExp1::mf3\n";}
    void mf4(){std::cout<<"Cl33_DerivedExp1::mf4\n";}
};

void Cl33_test02()
{
    int x =0;
    double y =0.0;
    Cl33_DerivedExp1 cl33dexp1;
    cl33dexp1.mf1();
    //cl33dexp1.mf1(x);发现调用失败，竟然查找不到从基类继承的函数,编译器报错。Derived(派生类)函数mf3遮掩了一个名为mf3但类型不通的Base(基类)函数
    cl33dexp1.mf2();
    cl33dexp1.mf3();
    //cl33dexp1.mf3(y);同mf1(int)一致
    cl33dexp1.mf4();
}
//怎么理解上面这种行为？答:是为了防止在程序库或应用框架内建立新的派生类时附带从基类继承重载函数。
//意思是:基类重载函数是继承到派生类的，但是被遮掩了。事实是,如果正在使用public继承又不继承那些重载函数，显然是违反了条款31的is-a关系的。

//例子4:解决例子3的基类重载函数被派生类同名函数遮掩问题
class Cl33_BaseExp2{
private:
    int x;
public:
    virtual void mf1() =0;
    virtual void mf1(int ){std::cout<<"Cl33_BaseExp2::mf1(int)\n";}
    virtual void mf2(){std::cout<<"Cl33_BaseExp2::mf2\n";}
    void mf3(){std::cout<<"Cl33_BaseExp2::mf3\n";}
    void mf3(double ){std::cout<<"Cl33_BaseExp2::mf3(int)\n";}
};
class Cl33_DerivedExp2:
        public Cl33_BaseExp2{
public:
    using Cl33_BaseExp2::mf1;//让Base class内名为mf1和mf3的所有东西都将在Derived作用域内可见(且public)
    using Cl33_BaseExp2::mf3;
    virtual void mf1(){std::cout<<"Cl33_DerivedExp2::mf1\n";}
    void mf3(){std::cout<<"Cl33_DerivedExp2::mf3\n";}
    void mf4(){std::cout<<"Cl33_DerivedExp2::mf4\n";}
};

void Cl33_test03()
{
    int x =0;
    double y =0.0;
    Cl33_DerivedExp2 cl33dexp1;
    cl33dexp1.mf1();
    cl33dexp1.mf1(x);//成功
    cl33dexp1.mf2();
    cl33dexp1.mf3();
    cl33dexp1.mf3(y);//成功
    cl33dexp1.mf4();
}

//例子4:当继承关系是private时，又会发生什么事？
class Cl33_BaseExp3{
public:
    virtual void mf1() =0;
    virtual void mf1(int){std::cout<<"Cl33_BaseExp3::mf1(int)\n";}
};
class Cl33_DerivedExp:
        private Cl33_BaseExp3{
public:
    //使用using让基类重载函数在派生类中暴露
    //using Cl33_BaseExp3::mf1;
    //virtual void mf1(){std::cout<<"Cl33_DerivedExp::mf1()\n";}

    //不适用using时 应该怎么调用基类重载函数呢？
    virtual void mf1(){Cl33_BaseExp3::mf1(1);}//inline转交函数
};

void Cl33_test04()
{
    int x =0;
    double y =0.0;
    Cl33_DerivedExp cl33dexp1;
    cl33dexp1.mf1();
   // cl33dexp1.mf1(x);//没有使用usings时失败,因为重载函数不能被继承
}

//inline转交函数得另一个用途是为那些不支持using声明式得老旧编译器开辟得另一条新路，将继承而得得名称汇入派生类作用域内。
/*重点记住:
 *  1.derived classes内的名称会遮掩base classes内的名称。(基类重载函数是继承到派生类的，但是被遮掩了。所以看起来像是没被继承一样)
 *  2.为了能让基类被遮掩的名称显现，可以适用using声明式或转交函数。
 */


#endif //EFFECTIVECPP_CLAUSE33_AVOID_HIDING_INHERITED_NAME_HPP
