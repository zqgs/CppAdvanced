//
// Created by Sea on 2021/9/9.
//

#ifndef EFFECTIVECPP_CL36_NEVER_REDEFINE_INHERITED_NON_VIRTUAL_FUNC_HPP
#define EFFECTIVECPP_CL36_NEVER_REDEFINE_INHERITED_NON_VIRTUAL_FUNC_HPP

#include <iostream>

//条款36:绝不重新定义继承而来的non-virtual函数

//直接看例子,例1:
class Cl36_B{
public:
    void mf(){std::cout<<"Cl36_B::mf\n";}
};
class Cl36_D: public Cl36_B{};


void Cl36_test01()
{
    Cl36_D x;
    Cl36_B* pB = &x;
    pB->mf();

    Cl36_D *pD = &x;
    pD->mf();
    //此时pB和pD体现出了相同的行为
}

//例2:如果派生类有了自己的行为，那么test01两个对象体现出的行为可能就并不相似了
class Cl36_D1: public Cl36_B{
public:
    void mf(){std::cout<<"Cl36_D1::mf\n";}
};
void Cl36_test02()
{
    Cl36_D1 x;
    Cl36_B* pB = &x;
    pB->mf();//调用的是基类

    Cl36_D1 *pD = &x;
    pD->mf();//调用的是派生类
    //此时pB和pD体现出了不相同的行为，出现这样的原因是non-virtual都是静态绑定。(virtual才是动态绑定)
    //静态绑定:pB永远调用Cl36_B的版本，pD永远调用Cl36_D1的版本。
    //动态绑定:无论是pD或pB都会调用Cl36_D1的版本。
}


/*观点一:条款32描述public继承意味着is-a关系。
 *观点二:条款34讲述class内声明一个non-virtual会为该类建立起一个不变性凌驾其特异性。
 *  如果这两个观点施行于例1的Cl36_B、Cl36_D以及non-virtual成员函数B::mf身上，那么要注意:
 *1.适用于B对象的每一件事，也适用于D对象，因为每个D对象都是一个B对象
 *2.B的derived classes一定会继承mf的接口和实现，因为mf是B的一个non-virtual
 *  注意:当基类的函数被声明为non-virtual时意味着不希望被派生类重新定义。
 */

/*重点记住:
 *  1.绝对不要重新定义继承而来的non-virtual函数
 */

#endif //EFFECTIVECPP_CL36_NEVER_REDEFINE_INHERITED_NON_VIRTUAL_FUNC_HPP
