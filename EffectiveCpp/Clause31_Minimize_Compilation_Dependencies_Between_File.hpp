//
// Created by Sea on 2021/8/25.
//

#ifndef EFFECTIVECPP_CLAUSE31_MINIMIZE_COMPILATION_DEPENDENCIES_BETWEEN_FILE_HPP
#define EFFECTIVECPP_CLAUSE31_MINIMIZE_COMPILATION_DEPENDENCIES_BETWEEN_FILE_HPP

#include <string>
#include <memory>
//条款31:将文件间的编译依存关系降至最低

//例子1:当一个class被轻微修改，和这个class相关的文件都被重新编译
//#include "Date.h"
//#include "Address"
class Cl31_Person
{
public:
    Cl31_Person(const std::string & name/*const Date& birthday,const Address& addr*/);
    std::string name() const;
    std::string birthday() const;
    std::string address() const;

private:
    std::string theName;
    //Date theBirthday;
    //Address theAddress;
};
//上面的例子在Person定义文件和其他含入文件直接形成了一种编译依存关系。如果这些头文件中有任何一个被改变,
//那么每一个含入Person class的文件就得重新编译。这种连串编译依存关系会对许多项目造成难以形容的灾难。


//怎么将接口和实现解耦合呢？ 答案:前置声明。但前置声明的每一件东西，编译器必须在编译期间知道对象的大小。
//例子2:考虑以下例子，我们用前置声明实现例子1
class Cl31_Date;
class Cl31_Address;
class Cl31_PersonExp1
{
public:
    Cl31_PersonExp1(const std::string & name,const Cl31_Date& birthday,const Cl31_Address& addr);
    std::string name() const;
    std::string birthday() const;
    std::string address() const;

private:
    std::string theName;
    //Cl31_Date theBirthday;
    //Cl31_Address theAddress;

};

void Cl31_Test01()
{
    //通常编译器知道int应该分配多少内存
    int x;
    //当编译器想要知道Cl31_Person需要分配多少内存时,唯一办法就是询问Cl31_Person的定义式。
    //当询问到前置声明Cl31_Date、Cl31_Address时，然而定义式可以合法的不列出实现，编译器如何知道要分配多少空间？
    Cl31_Person p("LiLi");

    //有一种办法，将对象实现隐藏在一个指针背后，比如:
    int *y;
    Cl31_Person *p1;
}

//例子3:改善一下例子2的前置声明，将Person分割为两个class，一个提供接口，一个负责实现该接口
//Cl31_PersonExp2.h
class Cl31_PersonImpl;
class Cl31_PersonExp2{
public:
    Cl31_PersonExp2(const std::string &Name);
    std::string name() const;
    ~Cl31_PersonExp2(){}
private:
    std::shared_ptr<Cl31_PersonImpl> pImpl;
};
//Cl31_PersonExp2.cpp包含Cl31_PersonImpl.h用于接口的实现
//这样的设计之下，Cl31_PersonExp2的接口完全与实现分离。无论是Cl31_PersonImpl修改任何东西，Cl31_PersonExp2都不再需要重新编译，此
//时通过接口时无法看到Cl31_PersonExp2的真正实现的,也就杜绝了"取决于实现"的代码。这才是"接口与实现分离"


//实现与接口分离的关键:以"声明的依存性"替换"定义的依存性"。尽最大可能让头文件自我满足。

/*以上描述的Handle class都源自于以下设计策略:
 *  1.如果使用对象引用(object references)或对象指针(object pointers)可以完成，就不要使用普通对象。可以只靠一个类型声明式就定义出指针该类型的引用
 *或指针。但如果定义某类型的object(对象)，就需要用到该类型的定义式。
 *  2.如果能够，尽量以class声明式替换class定义式。注意，当声明一个函数用到某个类时，其实并不需要该类的定义，即使函数以值传递的方式传递该类型的参数也是如此
 *  3.为声明式和定义式提供不同的头文件。
 */

//另一个制作Handle class办法是:令Person成为一种特殊的abstract base calss(抽象基类),称为interface class。这种class的目的是详细描述派生类的接口，因此通常不带
//成员变量，也没有构造函数，只有一个析构函数以及一组pure virtual函数(虚函数 or 纯虚函数),用来叙述整个接口

//例子4:针对Person而写的interface class
class Cl31_PersonExp3{
public:
    virtual ~Cl31_PersonExp3();
    virtual std::string name() const =0;
    virtual std::string birthDate() const =0;
    virtual std::string address() const =0;
};
//interface class的调用者通常调用一个特殊函数为新对象真正的实例化，那个就是派生类的构造函数，这样的函数通常称为"工厂函数"或者virtual构造函数，
//这些函数一般返回指针指向动态分配的内存，但这样的函数往往又在interface class内被声明为static
//例子5:
class Cl31_RealPerson;
class Cl31_PersonExp4{
public:
//    static std::shared_ptr<Cl31_PersonExp4> create(const std::string& name){
//        return std::shared_ptr<Cl31_PersonExp4>(new Cl31_RealPerson(name));
//    }
};
class Cl31_RealPerson: public Cl31_PersonExp4{
public:
    Cl31_RealPerson(const std::string& name):theName(name){}
    virtual ~Cl31_RealPerson(){}
    std::string name() const;
private:
    std::string theName;
};


/*  handle class的不足:成员函数必须通过Impl pointer指针取得对象数据。那会为每一次访问增加一层间接性。每一个对象小号的内存数量必须增加Impl pointer指针的
 *大小。最后Impl pointer指针必须初始化，指向一个动态分配得来Impl object，所以还得承受动态内存分配带来得额外开销，以及遭遇bad_alloc异常(内存不足)的可能。
 *
 *  interface class的不足:由于每一个函数都是virtual，所以必须为每次函数调用付出一个间接跳跃的成本(如条款07)。此外interface class派生类的对象必须内含一个虚函数表
 *这个指针可能会增加存在对象所需要的内存数量---实际取决于这个对象interface class之外是否还有其他的虚函数来源。
 */

//无论是handle class或interface class，一旦脱离inline函数都无法有太大的作为（如条款30解释了函数本体为了被inline必须置于头文件内）。但handle class和interface class
//正是特别被设计用来因此实现细节的。

//在实际开发过程中使用handle class或interface class以求实现码有所变化带给使用者的冲击最小。当它们(handle class或interface class)导致速度和/或大小差异过于重大
//以至于class间的耦合相形之下不成为关键，那么就以具象类(就是一个普通类)替换handle class或interface class。

/*重点记住:
 *  1.支持"编译依存最小化"的一般构想是:相依于声明式，不要相依于定义式。基于此构想的两个手段handle class或interface class。
 *  2.程序库头文件应该以"完全仅有声明式"的形式存在。这种做法不论是否涉及template都适用
 */


#endif //EFFECTIVECPP_CLAUSE31_MINIMIZE_COMPILATION_DEPENDENCIES_BETWEEN_FILE_HPP
