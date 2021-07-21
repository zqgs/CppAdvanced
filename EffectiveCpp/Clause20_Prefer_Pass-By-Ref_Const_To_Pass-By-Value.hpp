//
// Created by Sea on 2021/7/20.
//

#ifndef EFFECTIVECPP_CLAUSE20_PREFER_PASS_BY_REF_CONST_TO_PASS_BY_VALUE_HPP
#define EFFECTIVECPP_CLAUSE20_PREFER_PASS_BY_REF_CONST_TO_PASS_BY_VALUE_HPP

#include <iostream>
#include <string>

//条款20:宁以pass-by-reference-const(const引用传递)替换 pass-by-value(值传递)

/*值传递的过程解析:
 * 1.内置类型值传递被copy出一份副本,让副本去被函数内部调用。
 * 2.class/struct值传递时由对象copy构造函数产出，这可能使得对象值传递的操作消耗昂贵的时间
 */

//Count用来统计一个类的内方法被调用的次数，次数越多，表示函数调用成本越高
static int Cl20_Count = 0;
//例子1:清楚解析值传递和引用传递对象的产生的成本
class Cl20_Person{
public:
    Cl20_Person(){Cl20_Count++;std::cout<<"Cl20_Person is runing\n";}
    virtual ~Cl20_Person(){Cl20_Count++;std::cout<<"~Cl20_Person is runing\n";}//会发生继承
    Cl20_Person(const Cl20_Person& rhs){
        this->name = rhs.name;
        this->address = rhs.address;
        Cl20_Count++;
        std::cout<<"Cl20_Person Copying is runing\n";
    }
private:
    std::string name;
    std::string address;
};

class Cl20_Student: public Cl20_Person{
public:
    Cl20_Student(){Cl20_Count++;std::cout<<"Cl20_Student is runing\n";}
    ~Cl20_Student(){Cl20_Count++;std::cout<<"~Cl20_Student is runing\n";}

    Cl20_Student(const Cl20_Student& rhs){
        this->schoolName = rhs.schoolName;
        this->schoolAddress = rhs.schoolAddress;
        Cl20_Count++;
        std::cout<<"Cl20_Student Copying is runing\n";
    }
private:
    std::string schoolName;
    std::string schoolAddress;
};

bool validateSutdent01(Cl20_Student s){
    return true;
}
bool validateSutdent02(Cl20_Student &s){
    return true;
}
bool validateSutdent03(const Cl20_Student &s){
    return true;
}
void Cl20_test01(){
    //值传递
    Cl20_Count = 0;
    Cl20_Student sPlato;
    bool platoIsOK = validateSutdent01(sPlato);
    std::cout<<"Cl20_Count:"<<Cl20_Count<<"\n";

    //Cl20_Count = 6
}
void Cl20_test02(){
    //引用传递
    Cl20_Count = 0;
    Cl20_Student sPlato;
    bool platoIsOK = validateSutdent02(sPlato);
    std::cout<<"Cl20_Count:"<<Cl20_Count<<"\n";

    //Cl20_Count = 2
    //事实证明引用传递会节约程序的开销，除去class本身的开销外，还有成员变量string的构造和析构均需要程序的额外开销

    //当前调用并不是最佳，本意是通过引用来代替值传递，对象却在函数内部被修改。
}
void Cl20_test03(){
    //引用传递
    Cl20_Count = 0;
    Cl20_Student sPlato;
    bool platoIsOK = validateSutdent03(sPlato);
    std::cout<<"Cl20_Count:"<<Cl20_Count<<"\n";

    //Cl20_Count = 2
    //与test02传递效率一样的同时也保证的对象不可被修改
}



//引用传递可以消除对象切割现象
//对象切割现象详细介绍:所谓“切割”，就是当一个子类对象通过值传递给基类对象，
//这个基类的拷贝构造函数将被调用，也就是说此时生成由子类对象拷贝构造了一个基类对象，
//该对象失去了子类的所有特性，退化成了完全的基类对象。所以当我们向上转型如果不用引用或指针,对象将被切割。
//例2:对象切割现象体现
class Cl20_Window{
public:
    virtual std::string name()const{return std::string("Window");}
    virtual void display() const{std::cout<<"Cl20_Window::display!\n";}
};
class WindowWithScrollBars: public Cl20_Window{
public:
    std::string name()const override{return std::string("WindowWithScrollBars");}
    void display() const override {std::cout<<"WindowWithScrollBars::display!\n";}
};

void printNameAndDisplay01(Cl20_Window w)
{
    std::cout<<"DisplayWindowName:"<<w.name()<<"\n";
    w.display();
}
void printNameAndDisplay02(const Cl20_Window &w)
{
    std::cout<<"DisplayWindowName:"<<w.name()<<"\n";
    w.display();
}
void printNameAndDisplay03(const Cl20_Window *w)
{
    std::cout<<"DisplayWindowName:"<<w->name()<<"\n";
    w->display();
}
void Cl20_test04()
{
    //值传递发生对象切割，派生类特性完全消失，只保留基类特性。
    WindowWithScrollBars wsb1;
    printNameAndDisplay01(wsb1);

    //引用传递，可以消除对象切割
    printNameAndDisplay02(wsb1);

    //指针传递，可以消除对象切割.所有派生类特性得以保留
    printNameAndDisplay03(dynamic_cast<Cl20_Window *>(&wsb1));

    //其实引用往往是以指针的形式实现出来的，因此传递引用通常意味着传递的是指针。
    //内置类型的值传递效率要比引用传递要高
}

/*重点记住:
 * 1.好尽量以pass-by-reference-const代替py-by-value.前者通常比较高效，并可避免切割问题。
 * 2.以上规则并不适用于内置类型(如ints,chars等等)，以及STL的迭代器和函数对象。对它们而言
 *往往pass-by-value往往比较适当
 */

#endif //EFFECTIVECPP_CLAUSE20_PREFER_PASS_BY_REF_CONST_TO_PASS_BY_VALUE_HPP
