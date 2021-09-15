//
// Created by Sea on 2021/9/15.
//

#ifndef EFFECTIVECPP_CLAUSE40_USE_MULTIPLE_INHERITANCE_JUDICIOUSLY_HPP
#define EFFECTIVECPP_CLAUSE40_USE_MULTIPLE_INHERITANCE_JUDICIOUSLY_HPP

#include <iostream>
#include <string>
//����40:���Ƕ�������ʹ�ö��ؼ̳�

//��1:���������һ�����ϵ�base class�̳���ͬ����(��:������typydef��)���µ����壿
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
    //mp.CheckOut();//���ֵ��ò��ˣ���Ȼ���������塣����˵������һ����public��һ����private��Ӧ�õ��õ���public�ĺ�������������ˡ�
    //C++�������غ������ù���:�ڿ����Ƿ��и�������ȡ��֮ǰ��C++����ȷ����������Դ˵����Ƿ������ƥ�䣬ֱ���ҵ����ƥ���������á�
    //����������CheckOut��ƥ��̶���һ���ġ����Ա��������δͨ��
    mp.Cl40_BorrowAbleItem::CheckOut();//����ָ�����ò�����ȷ��
}

//��2:���Ƕ��ؼ̳��е���ʯ�ͼ̳�,��Ա����ݿ��������⣿
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
    //cf.fileName="";//����ͨ����
    cf.Cl40_InputFile::fileName = "hello";
    cf.Cl40_OutFile::fileName = "World";
    //���˴���fileName��Ա������InFile��OutFile�ֱ𿽱���һ�Σ�Ҳ�ͳ����˶�ݿ���������
    //IOFile����ֻ����һ�����ƣ����Լ̳��������������fileName�����ظ�
}

//��3:��ν�����Ƕ��ؼ̳��е���ʯ�ͼ̳�,��Ա����ݿ��������⣿ --->virtual�̳�
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
    cf.fileName="hello world";//�ɹ�����
    cf.Cl40_InputFile_Exp1::print();
    cf.Cl40_OutFile_Exp1::print();
}
//�ܽ�:�κ�ʱ��ʹ��public�̳�ʱ�������virtual public�̳С�
//�����ܽ�۵���˵����ȷ�ģ�����virtual�̳б�non-virtual�̳������(ԭ��:�麯����)��������ε�ʹ��virtual�̳�ʱ�͵ø�����Ӧ�Ĵ��ۡ�
//virtual�̳еĳɱ�������:virtual base class��ʼ��������,��һ���������������̳���ϵ�����۾���base�ж�Զ����������е�virtual base(ֱ�ӻ���)�ĳ�ʼ������

//����virtual base��ʹ��:
//1.�Ǳ�Ҫ��ʹ��virtual base��ƽʱ��ʹ��non-virtual�̳С�
//2.�������ʹ��virtual base class�������ܵı��������з������ݡ�


//��4������һ�����ؼ̳е�ʾ����"public�̳�ĳ��interface class"��"private�̳�ĳ��Э��ʵ�ֵ�class"�����
//����ӿ���
class Cl40_IPerson{
public:
    virtual ~Cl40_IPerson(){}
    virtual std::string name() const =0;
    virtual std::string birthDate() const =0;
};
class Cl40_DateBaseID{};
//���ɸ����õĺ�����
class Cl40_PersonInfo{
public:
    explicit Cl40_PersonInfo(Cl40_DateBaseID pid){}
    virtual ~Cl40_PersonInfo(){}
    virtual const char* theName() const{return "";}
    virtual const char* theBirthDate() const{return "";}
    virtual const char* valueDelimOpen() const{return "";}
    virtual const char* valueDelimClose() const{return "";}
};

//������
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
//  ���ؼ̳�ֻ��������󹤾������һ�����߶��ѡ�����һ�̳У����ؼ̳и��Ӹ��ӡ������ʹ�õ�һ�̳�ʵ�֣���ô����ѡ��һ�̳С�
//������ؼ̳е�ȷ�������������ġ�����ά�����������������Ǿ�ֱ��ѡ����ؼ̳С�

/*�ص��ס:
 *  1.���ؼ̳бȵ�һ�̳и��ӡ������ܵ����µ������ԣ��Լ���virtual�̳е���Ҫ��
 *  2.virtual�̳л����Ӵ�С���ٶȡ���ʼ��(����ֵ)���Ӷȵȵȳɱ������virtual base class�����κ����ݣ�����������ֵ�ÿ��Ǻ�ʹ�á�
 *  3.���ؼ̳е���ȷ��;������һ������漰"public�̳�ĳ��interface class"��"private�̳�ĳ��Э��ʵ�ֵ�class"������ϡ�
 */

#endif //EFFECTIVECPP_CLAUSE40_USE_MULTIPLE_INHERITANCE_JUDICIOUSLY_HPP
