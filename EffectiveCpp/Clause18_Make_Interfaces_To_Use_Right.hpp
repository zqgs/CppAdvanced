//
// Created by Sea on 2021/7/20.
//

#ifndef EFFECTIVECPP_CLAUSE18_MAKE_INTERFACES_TO_USE_RIGHT_HPP
#define EFFECTIVECPP_CLAUSE18_MAKE_INTERFACES_TO_USE_RIGHT_HPP
#include <memory>
#include <iostream>
//条款18:让接口容易被正确使用，不易被误用

//例1:接口滥用
class Cl18_Date{
public:
    Cl18_Date(int mouth,int Day,int Year){}
};
void Cl18_Test01(){
    Cl18_Date cd1(10,2,1995);//正确传值
    Cl18_Date cd2(2,30,1995);//XJB传值
}

//例2：对例1改善之后
//通过外覆类型(wrapper types)来区别年月日
struct _Cl18Year{
    explicit _Cl18Year(int y):val(y){}
    int val;
};
struct _Cl18Mouth{
    explicit _Cl18Mouth(int m):val(m){}
    int val;
};
struct _Cl18Day{
    explicit _Cl18Day(int d):val(d){}
    int val;
};

//如果有些条件已经确定了，直接采用enum枚举这些类型
//枚举月份
class Cl18_Mouth{
public:
    static _Cl18Mouth Jan(){return _Cl18Mouth(1);}
    //....
    static _Cl18Mouth Dec(){return _Cl18Mouth(12);}

private:
    explicit Cl18_Mouth(int m){}//阻止产生新的类型
};

//通过外覆类型构建新的日期
class  Cl18_DateExp1{
public:
    Cl18_DateExp1(const _Cl18Year& yy,const _Cl18Mouth& mm,const _Cl18Day& dd){

    }
};

void Cl18_Test02(){
    Cl18_DateExp1 cd1(_Cl18Year(1995),Cl18_Mouth::Dec(),_Cl18Day(30));
}

//另一个一般性准则:让types容易被正确使用，不易被误用。
//除非有更好的理由，否则应该尽量令types的行为与内置types一致。
//避免无端与内置类型不兼容，理由是为了提供行为一致的接口。



//如果指望调用者每次都记得必须做某件事情，就意味着程序有可能产生"不正确使用"的倾向
//例3:条款13中的例子factory函数中返回一个指向继承体系的动态分配对象
class Cl18_Investment{
public:
    void Print(){std::cout<<"Cl18_Investment::Print\n";}
};
Cl18_Investment* CreateInvestment(){return new Cl18_Investment();}

void Cl18_Test03()
{
    //未引入智能指针
    Cl18_Investment *inv = CreateInvestment();
    //客户一定要记得调用delete，否则则引发内存泄漏
    delete inv;

    //引入智能指针后，将delete的责任推给了智能指针
    std::shared_ptr<Cl18_Investment> pInv(CreateInvestment());
    
    //但是如果用户忘记了使用智能指针怎么办？
}

//强制让用户使用智能指针
std::shared_ptr<Cl18_Investment> CreateInvestmentSharePtr()
{
    std::shared_ptr<Cl18_Investment> pInv(new Cl18_Investment());
    return pInv;
}

//智能指针share_ptr强大的地方在于可以配置删除器(deleter)
void _clause18_GetRidInvestment(Cl18_Investment *pm){
    if(pm)
     delete pm;
    std::cout<<"deleter:_clause18_GetRidInvestment is exec\n";
}
//配置了删除器的智能指针
std::shared_ptr<Cl18_Investment> CreateInvestmentSharePtrExp1()
{
    //share_ptr的特性:它会自动使用它的"每个指针专属的删除器"
    std::shared_ptr<Cl18_Investment> pInv(new Cl18_Investment(),_clause18_GetRidInvestment);
    return pInv;
}

void Cl18_Test04()
{
    std::shared_ptr<Cl18_Investment> ptr = CreateInvestmentSharePtrExp1();
    ptr->Print();
}

//使用share_ptr还可以避免cross-DLL problem(动态链接库跨域问题)
//例4:跨DLL使用new和delete问题，会导致运行期错误
void* Cl18_DLL1_CteateMemory()
{
    char*p = new char[8];
    return static_cast<void*>(p);
}
void Cl18_DLL2_DeleteMemory(void* p)
{
    if(p){
        delete [] p;
    }
}

//如果使用share_ptr则可以避开DLL跨域问题
//例5:
class Cl18_Stock: public Cl18_Investment
{

};

//此时无论share_ptr被传递给任何DLLs，无需在意跨域问题。当引用次数为0时，自动调用对应的deleter删除器
//注:当share_ptr所离开作用域时引用次数会被减一，当为0时调用删除器
std::shared_ptr<Cl18_Investment> CreateInvestmentSharePtrExp2()
{
    return std::shared_ptr<Cl18_Investment>(new Cl18_Stock);
}

/*share_ptr的使用成本:
 * 1.share_ptr是原始指针的两倍大小:以动态分配内存作为记录用途和"删除器的专属数据"，以virtual形式
 *调用删除器，并在多线程程序修改引用次数时承受线程同步化的额外开销，比原始指针大且慢，使用了辅助
 *动态内存。
 * 2.相比之下，share_ptr的执行成本扩张比起降低客户的错误成效是显著的。
 */

/*重点记住:
 * 1.好的接口很容易被正确使用，不容易被误用。应该在所有的接口中努力达成这些性质
 * 2."促进正确使用"的办法包括接口的一致性(例如：STL的接口基本上保持一致性)，以及与内置类型的行为兼容。
 * 3."阻止误用"的办法包括建立新类型、限制类型上的操作、束缚对象值、以及消除客户的资源管理责任
 * 4.share_ptr支持定制型删除器。这可防范DLL问题，可被用来自动解除互斥锁(条款14中的class-Clause14_LockExp1)。
 */

#endif //EFFECTIVECPP_CLAUSE18_MAKE_INTERFACES_TO_USE_RIGHT_HPP
