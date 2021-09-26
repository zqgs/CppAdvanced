//
// Created by Sea on 2021/9/23.
//

#ifndef EFFECTIVECPP_CLAUSE45_USE_MEMBER_FUN_TEMPLATE_TO_ACCEPT_ALL_COMPATIBLE_TYPES_HPP
#define EFFECTIVECPP_CLAUSE45_USE_MEMBER_FUN_TEMPLATE_TO_ACCEPT_ALL_COMPATIBLE_TYPES_HPP

#include <iostream>
#include <memory>
//条款45:运用成员函数模板接收所有兼容类型
//智能指针:是指"行为像指针"的对象，并提供指针没有的机能。

//例子1:真实指针是可以支持隐式转换的。
class Cl45_Top{
public:
    virtual void print_top(){std::cout<<"Cl45_Top\n";}
};
class Cl45_Middle: public Cl45_Top{
public:
     void print_top(){std::cout<<"Cl45_Middle\n";}
};
class Cl45_Bottom: public Cl45_Middle{
public:
    void print_top(){std::cout<<"Cl45_Bottom\n";}
};

void Cl45_test01()
{
    Cl45_Top* pt1 = new Cl45_Middle();
    pt1->print_top();

    Cl45_Top* pt2 = new Cl45_Bottom();
    pt2->print_top();

    const Cl45_Top* pct2 = pt1;
}

//例子2:如果想自定的智能指针完成上述转换，那稍微会有点麻烦
template<typename T>
class Cl45_SmartPtr{
public:
    Cl45_SmartPtr
    (T* readPtr)
    {
        tPtr = readPtr;
    }
    Cl45_SmartPtr& operator=(const Cl45_SmartPtr& rhs)
    {
        if (this != &rhs)
        {
            this->tPtr = rhs.tPtr;
        }
        return *this;
    }

private:
    T* tPtr;
};

void Cl45_test02()
{
    //Cl45_SmartPtr<Cl45_Top> pt1 = Cl45_SmartPtr<Cl45_Middle>(new Cl45_Middle());
    //Cl45_SmartPtr<Cl45_Top> pt1 = Cl45_SmartPtr<Cl45_Bottom>(new Cl45_Bottom());
    //发生上述编译器是报错的。原因是:相同template产生出的两个具现体编译器将其视为完全不同的class。
}

//怎样才能编写通得过编译器审查的智能指针呢?
//直观看来应该用Cl45_SmartPtr<Cl45_Middle>或Cl45_SmartPtr<Cl45_Bottom>构造出一个Cl45_SmartPtr<Cl45_Top>这样的构造函数。
//如果日后有所扩充，Cl45_SmartPtr<Cl45_Top>对象又必须根据其他智能指针构造自己。

//因此，就原理而言，我们需要的构造函数将没有止境，因为一个template可以被无限量的具现化，以致于生成无限量函数。因此我们不是为了Cl45_SmartPtr<Cl45_Top>写
//一个构造函数，而是为它写一个构造模板，这样的模板称之为member function template(成员函数模板),其作用是为class生成函数。

//例子3:来看具体实现
template <typename T>
class Cl45_SmartPtr_Exp{
public:
    Cl45_SmartPtr_Exp() = default;
    Cl45_SmartPtr_Exp(T* readPtr)
    {
        tHeldPtr = readPtr;
    }
    ~Cl45_SmartPtr_Exp()
    {
        std::cout << "Cl45_SmartPtr_Exp:Destructo" << std::endl;
    }

    template<typename U>
    Cl45_SmartPtr_Exp(const Cl45_SmartPtr_Exp<U>& readPtr)://省略explicit是为了支持隐式转换
    //使用成员初值列来初始化Cl45_SmartPtr_Exp<T>之类类型为T的成员变量，并以类型为U*的指针作为初值。
    //这种行为只有当"存在某个隐式转换可将一个U*指针转为T*指针"时才能通过编译。
    tHeldPtr(readPtr.get())

    {std::cout << "Cl45_SmartPtr_Exp:CopyConstructor" << std::endl;}
    T* get() const{return tHeldPtr;}

public:
    void Call(){tHeldPtr->print_top();}
private:
    T* tHeldPtr;
};
void Cl45_test03()
{
    Cl45_SmartPtr_Exp<Cl45_Middle> spd(new Cl45_Middle());
    Cl45_SmartPtr_Exp<Cl45_Top> spb(spd);
}

//member function template(成员函数模板)的效用不仅限于构造函数，也可用来支持赋值操作，如:share_ptr可以来自兼容的内置指针以及除weak_ptr之类的赋值操作。
//例子4:来看一下share_ptr的实现
template <typename T>
class Cl45_Shareptr{
public:
    //构造
    template<typename Y>
    explicit Cl45_Shareptr(Y* p){}//内置指针
    template<typename Y>
    explicit Cl45_Shareptr(std::shared_ptr<Y> const& p){}//shared_ptr指针
    template<typename Y>
    explicit Cl45_Shareptr(std::weak_ptr<Y> const& p){}//weak_ptr指针
    template<typename Y>
    explicit Cl45_Shareptr(std::auto_ptr<Y> const& p){}//auto_ptr指针

    //赋值
    template<typename Y>
    Cl45_Shareptr& operator=(std::shared_ptr<Y> const& r){}
    template<typename Y>
    Cl45_Shareptr& operator=(std::auto_ptr<Y> const& r){}
};

//以上构造函数都是显式的，除了"泛化copy构造函数除外"。
//member function template(成员函数模板)是个奇妙的东西，但是他们并不改变语言基本规则。条款05描述，编译器会为我们生成4个函数。
//std::share_ptr声明了一个繁华copy构造，一旦类型T和Y相同，泛化拷贝构造函数会被具现化为"正常的拷贝构造函数"。那么编译器是否会暗自生成一个copy构造函数呢？
//或当某个share_ptr对象根据另一个同型share_ptr对象展开构造时，编译器会将"泛化拷贝构造函数模板"具现化吗？

//重点记住:成员函数不会改变语言规则。如果程序需要一个拷贝构造函数，你却没有声明，那么编译器会暗自生成一个。
//在class内声明泛化的拷贝构造函数并不会组织编译器生成自己的拷贝构造函数，所以如果想要控制copy的方放面面，那么必须得同时声明泛化和非泛化函数。


/*重点记住:
 *  1.请使用member function template(成员函数模板)生成"可接受所有内容类型"的函数。
 *  2.如果声明member用于"泛化copy构造"或"泛化赋值操作"，还是需要声明正常的copy构造函数和copy赋值操作符。
 */

#endif //EFFECTIVECPP_CLAUSE45_USE_MEMBER_FUN_TEMPLATE_TO_ACCEPT_ALL_COMPATIBLE_TYPES_HPP
