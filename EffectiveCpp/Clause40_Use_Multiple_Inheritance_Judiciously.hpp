//
// Created by Sea on 2021/9/15.
//

#ifndef EFFECTIVECPP_CLAUSE40_USE_MULTIPLE_INHERITANCE_JUDICIOUSLY_HPP
#define EFFECTIVECPP_CLAUSE40_USE_MULTIPLE_INHERITANCE_JUDICIOUSLY_HPP

#include <iostream>
#include <string>
//条款40:明智而审慎地使用多重继承

//例1:怎样避免从一个以上的base class继承相同名称(如:函数、typydef等)导致的歧义？
class Cl40_BorrowAbleItem{
public:
    void CheckOut(){std::cout<<"this is Base class Cl40_BorrowAbleItem::CheckOut\n";}
};
class Cl40_ElectronicGadget{
private:
    void CheckOut(){std::cout<<"this is Base class Cl40_ElectronicGadget::CheckOut\n";}
};

class Cl40_Mp3Player:
        public Cl40_BorrowAbleItem,
        public Cl40_ElectronicGadget{

};
void
Cl40_test01()
{
    Cl40_Mp3Player mp;
    //mp.CheckOut();//发现调用不了，竟然产生了歧义。按理说基类中一个是public，一个是private，应该调用的是public的函数，但并非如此。
    //C++解析重载函数调用规则:在看到是否有个函数可取用之前，C++首先确认这个函数对此调用是否是最佳匹配，直至找到最佳匹配才允许调用。
    //本例的两个CheckOut的匹配程度是一样的。所以编译器审查未通过
    mp.Cl40_BorrowAbleItem::CheckOut();//这样指定调用才是正确的
}

//例2:考虑多重继承中的钻石型继承,成员被多份拷贝的问题？
class
Cl40_File
{
public:
    std::string fileName;
};
class Cl40_InputFile: public Cl40_File{
    void print(){std::cout<<"Cl40_InputFile::print:"<<fileName<<"\n";}

};
class Cl40_OutFile: public Cl40_File{
    void print(){std::cout<<"Cl40_OutFile::print:"<<fileName<<"\n";}
};
class Cl40_IOFile
:public Cl40_InputFile,
 public Cl40_OutFile
 {
};

void
Cl40_test02()
{
    Cl40_IOFile cf;
    //cf.fileName="";//歧义通不过
    cf.Cl40_InputFile::fileName = "hello";
    cf.Cl40_OutFile::fileName = "World";
    //到此处，fileName成员变量被InFile和OutFile分别拷贝了一次，也就出现了多份拷贝的问题
    //IOFile对象只改有一个名称，所以继承两个基类而来的fileName不该重复
}

//例3:如何解决考虑多重继承中的钻石型继承,成员被多份拷贝的问题？ --->virtual继承
class
Cl40_InputFile_Exp1:
    virtual public Cl40_File
{
public:
    void print(){std::cout<<"Cl40_InputFile_Exp1::print:"<<fileName<<"\n";}
};
class
Cl40_OutFile_Exp1:
    virtual public Cl40_File
{
public:
    void print(){std::cout<<"Cl40_OutFile_Exp1::print:"<<fileName<<"\n";}
};
class
Cl40_IOFile_Exp3:
    public Cl40_InputFile_Exp1,
    public Cl40_OutFile_Exp1
{

};

void
Cl40_test03()
{
    Cl40_IOFile_Exp3 cf;
    cf.fileName="hello world";//成功！！
    cf.Cl40_InputFile_Exp1::print();
    cf.Cl40_OutFile_Exp1::print();
}
//总结:任何时候使用public继承时，请改用virtual public继承。
//以上总结观点虽说是正确的，但是virtual继承比non-virtual继承体积大(原因:虚函数表)。无论如何当使用virtual继承时就得付出相应的代价。
//virtual继承的成本还包括:virtual base class初始化的问题,当一个派生类加入这个继承体系，不论距离base有多远，它都必须承担virtual base(直接或间接)的初始化责任

//关于virtual base的使用:
//1.非必要不使用virtual base。平时请使用non-virtual继承。
//2.如果必须使用virtual base class，尽可能的避免再其中放置数据。


//例4：来看一个多重继承的示例。"public继承某个interface class"和"private继承某个协助实现的class"的组合
//抽象接口类
class Cl40_IPerson{
public:
    virtual ~Cl40_IPerson(){}
    virtual std::string name() const =0;
    virtual std::string birthDate() const =0;
};
class Cl40_DateBaseID{};
//若干个有用的函数类
class Cl40_PersonInfo{
public:
    explicit Cl40_PersonInfo(Cl40_DateBaseID pid){}
    virtual ~Cl40_PersonInfo(){}
    virtual const char* theName() const{return "";}
    virtual const char* theBirthDate() const{return "";}
    virtual const char* valueDelimOpen() const{return "";}
    virtual const char* valueDelimClose() const{return "";}
};

//派生类
class Cl40_CPerson:
        public Cl40_IPerson,
        private Cl40_PersonInfo
{
public:
    explicit Cl40_CPerson(Cl40_DateBaseID pid):Cl40_PersonInfo(pid){}

    std::string
    name() const
    {return theName();}

    std::string
    birthDate() const
    {return theBirthDate();}

private:
    const char*
    valueDelimOpen() const override
    {return "[";}
    const char*
    valueDelimClose() const override
    {return "]";}
    const char* theName() const override
    {return "hello Tom";}
    const char* theBirthDate() const override
    {return "1995-09-23";}
};

void
Cl40_test04()
{
    Cl40_DateBaseID pid;

    Cl40_IPerson* iP = new Cl40_CPerson(pid);
    std::cout<<"Name:"<<iP->name()<<"\n";
    std::cout<<"birthDate:"<<iP->birthDate()<<"\n";

    delete iP;
}
//  多重继承只是面向对象工具箱里的一个工具而已。比起单一继承，多重继承更加复杂。如果能使用单一继承实现，那么果断选择单一继承。
//如果多重继承的确是完成任务最简洁的、最易维护、最合理的做法，那就直接选择多重继承。

/*重点记住:
 *  1.多重继承比单一继承复杂。它可能导致新的歧义性，以及对virtual继承的需要。
 *  2.virtual继承会增加大小、速度、初始化(及赋值)复杂度等等成本。如果virtual base class不带任何数据，那它将会是值得考虑和使用。
 *  3.多重继承的正确用途。其中一个情节涉及"public继承某个interface class"和"private继承某个协助实现的class"两相组合。
 */

#endif //EFFECTIVECPP_CLAUSE40_USE_MULTIPLE_INHERITANCE_JUDICIOUSLY_HPP
