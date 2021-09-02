//
// Created by Sea on 2021/9/2.
//

#ifndef EFFECTIVECPP_CLAUSE34_DISTINGUISHING_BETWEEN_INTERFACE_INHERITANCE_AND_IMPLEMENTATION_INHERITANCE_HPP
#define EFFECTIVECPP_CLAUSE34_DISTINGUISHING_BETWEEN_INTERFACE_INHERITANCE_AND_IMPLEMENTATION_INHERITANCE_HPP

#include <iostream>
#include <string>

//条款34:区分接口继承和实现继承

//思考:身为class设计者，有时候希望派生类只继承成员函数的接口。有时又希望派生类同时继承函数的接口和实现，
//但又希望能够覆写它们所继承的实现。有时又希望派生类同时继承函数函数的接口和实现，并且不允许覆写任何东西

//例子1:带有virtual都是抽象类，不能进行实例化
class Cl34_Shape{
public:
    virtual void draw() const =0;//接口
    virtual void error(const std::string& msg){std::cout<<"ERROR:"<<msg<<"\n";}//接口+默认实现
    int objectID() const{std::cout<<"objectID\n";return 0;}//接口和强制实现
};
void Cl34_Shape::draw() const {
    std::cout<<"Cl34_Shape::draw\n";
}
//Cl34_Shape是一个抽象类，使用者不能创建实体，只能创建派生类实体。Cl34_Shape强烈的影响所有public形式继承它的派生类。
//因为:成员函数的接口总会被继承。public意味着is-a,对基类为真的任何事对其派生类一定为真。

//关于Cl34_Shape类，我们逐一来看:
//pure virtual(纯虚函数)有两个突出特性:
//1.它们必须被任何"继承的"具象类重新声明(意思是:只要继承的类中含有纯虚函数,那么在派生类中一定要对其实现)。
//2.纯虚函数在抽象类中通常没有定义。(但如果强行给纯虚函数一份实现,C++并不会报错，但调用的唯一途径是通过派生类)
//总结:声明一个pure virtual函数的目的就是为了派生类只继承函数接口


class Cl34_Rectangle: public Cl34_Shape{
public:
    void draw() const override{std::cout<<"Cl34_Rectangle::draw\n";}
};
class Cl34_Ellipse: public Cl34_Shape{
    void draw() const override{std::cout<<"Cl34_Ellipse::draw\n";}
};

void Cl34_test01(){
    //Cl34_Shape* ps = new Cl34_Shape();//错误，Cl34_Shape是抽象的
    Cl34_Shape* ps1 = new Cl34_Rectangle();
    ps1->draw();
    Cl34_Shape* ps2 = new Cl34_Ellipse();
    ps2->draw();

    ps1->Cl34_Shape::draw();
    ps2->Cl34_Shape::draw();

    delete ps1;
    delete ps2;
}

//impure virtual(非纯虚函数):与纯虚函数不同的是,不需要派生类强制实现,但需要基类提供一份缺省版本，派生类可以对它覆写。
//声明一个impure virtual(非纯虚函数)的目的:让派生类继承该函数的接口和缺省实现。
//例如:Cl34_Shape::error(...),可以让派生类自己处理，如果派生类需要处理特殊错误，那么可以重写该函数。如果和基类的函数一样，那么直接使用缺省版本即可。
//例子2:允许impure virtual函数同时指定函数声明和缺省行为，却有可能造成危险。
class Cl34_Airport{
    //用以表现机场
public:
    std::string strAddress;
};
//飞机
class Cl34_Airplane{
public:
    virtual void fly(const Cl34_Airport& destnation){std::cout<<"Cl34_Airplane::fly to "<<destnation.strAddress<<"\n";}
};
//A型号和B型号的飞机 且 AB型号的飞机都是相同的飞行方式
class Cl34_ModelA: public Cl34_Airplane{};
class Cl34_ModelB: public Cl34_Airplane{};

//假设新增一个型号C的航线，飞行方式不同
class Cl34_ModelC: public Cl34_Airplane{
    //由于项目紧急，忘记重新定义C型号飞机需要飞行的方式,那么这将是个大灾难
};
void Cl34_test02()
{
    Cl34_Airport PDX;//选择一个机场
    PDX.strAddress = "HongQiao";//机场位于上海虹桥

    Cl34_Airplane *pa = new Cl34_ModelC();//选择一架飞机,并指定C型飞机承担飞行任务,但C的飞行方式与默认缺省的飞行方式是不一致的
    pa->fly(PDX);//调用了基类的缺省函数
    delete pa;
}

//问题不在基类Cl34_Airplane::fly的缺省行为,而在于Model C为能提供C的重写版本,导致调用了基类缺省版本。
//例子3:如何避免这种情况？答:我们需要切断"virtual函数接口"和其"缺省实现"之间的连接
class Cl34_Airplane_Exp1{
public:
    virtual void fly(const Cl34_Airport& destnation) = 0;//选用纯虚函数，让派生类强制实现飞行方式
};
//提供一份通用版本的飞行方式
void Cl34_Airplane_Exp1::fly(const Cl34_Airport &destnation)
{
    std::cout<<"Cl34_Airplane::fly to "<<destnation.strAddress<<"\n";
}

//A型号和B型号的飞机 且 AB型号的飞机都是相同的飞行方式
class Cl34_ModelA_exp1: public Cl34_Airplane_Exp1{
public:
    void fly(const Cl34_Airport& destnation) override{
        Cl34_Airplane_Exp1::fly(destnation);//调用基类的通用版本
    }
};
class Cl34_ModelB_exp1: public Cl34_Airplane_Exp1{
public:
    void fly(const Cl34_Airport& destnation) override{
        Cl34_Airplane_Exp1::fly(destnation);//调用基类的通用版本
    }
};
//新增的一个型号C的飞机，飞行方式不同
class Cl34_ModelC_exp1: public Cl34_Airplane_Exp1{
public:
    void fly(const Cl34_Airport& destnation) override{
        std::cout<<"Cl34_ModelC_exp1::fly to "<<destnation.strAddress<<"\n";
    }
};
void Cl34_test03()
{
    Cl34_Airport PDX;//选择一个机场
    PDX.strAddress = "PuDong";//机场位于上海浦东

    Cl34_Airplane_Exp1 *pa = new Cl34_ModelC_exp1();//选择一架飞机,并指定C型飞机承担飞行任务
    pa->fly(PDX);//调用方式和例子2基本上一致,却实打实选择对了正确的飞行方式。感谢纯虚函数的功劳
    delete pa;
}


//  最后来看non-virtual(非虚函数):当基类中的函数不是虚函数时,意味着不希望派生类诞生与基类不同的版本。任何派生类都不应该尝试改变其行为，由于non-virtual
//函数代表的意义时不变性凌驾特异性，所以它绝不该在派生类中重新定义。
//声明一个non-virtual(非虚函数)的目的:为了令派生类继承函数的接口和一份强制性的实现。


//  总结:pure virtual函数、impure virtual函数、non-virtual函数之间的差异，分别代表派生类想要继承的东西:只继承接口，或是继承接口和一份缺省实现，
//或是继承接口和一份强制实现。

//  常犯的错误(但不绝对):1.将所有成员函数都声明为non-virtual函数,这使得派生类没有剩余空间进行特化工作。如果并不想设计一个基类的话，那non-virtual就是合理的。
//2.将所有的成员函数都声明为virtual函数。有时是正确的(例如:条款31的interface class),然而大部分时候某些函数就不该在派生类中被重新定义。

/*重点记住:
 *  1.接口继承和实现继承不通。在public继承下，派生类总是继承基类的接口
 *  2.pure virtual纯虚函数只具体指定接口继承
 *  3.impure virtual 非纯虚函数具体指定接口继承及缺省实现继承
 *  4.non-virtual非虚函数具体指定接口以及强制性实现继承
 */






#endif //EFFECTIVECPP_CLAUSE34_DISTINGUISHING_BETWEEN_INTERFACE_INHERITANCE_AND_IMPLEMENTATION_INHERITANCE_HPP
