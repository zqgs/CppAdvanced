//
// Created by Sea on 2021/7/20.
//

#ifndef EFFECTIVECPP_CLAUSE20_PREFER_PASS_BY_REF_CONST_TO_PASS_BY_VALUE_HPP
#define EFFECTIVECPP_CLAUSE20_PREFER_PASS_BY_REF_CONST_TO_PASS_BY_VALUE_HPP

#include <iostream>
#include <string>

//����20:����pass-by-reference-const(const���ô���)�滻 pass-by-value(ֵ����)

/*ֵ���ݵĹ��̽���:
 * 1.��������ֵ���ݱ�copy��һ�ݸ���,�ø���ȥ�������ڲ����á�
 * 2.class/structֵ����ʱ�ɶ���copy���캯�������������ʹ�ö���ֵ���ݵĲ������İ����ʱ��
 */

//Count����ͳ��һ������ڷ��������õĴ���������Խ�࣬��ʾ�������óɱ�Խ��
static int Cl20_Count = 0;
//����1:�������ֵ���ݺ����ô��ݶ���Ĳ����ĳɱ�
class Cl20_Person{
public:
    Cl20_Person(){Cl20_Count++;std::cout<<"Cl20_Person is runing\n";}
    virtual ~Cl20_Person(){Cl20_Count++;std::cout<<"~Cl20_Person is runing\n";}//�ᷢ���̳�
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
    //ֵ����
    Cl20_Count = 0;
    Cl20_Student sPlato;
    bool platoIsOK = validateSutdent01(sPlato);
    std::cout<<"Cl20_Count:"<<Cl20_Count<<"\n";

    //Cl20_Count = 6
}
void Cl20_test02(){
    //���ô���
    Cl20_Count = 0;
    Cl20_Student sPlato;
    bool platoIsOK = validateSutdent02(sPlato);
    std::cout<<"Cl20_Count:"<<Cl20_Count<<"\n";

    //Cl20_Count = 2
    //��ʵ֤�����ô��ݻ��Լ����Ŀ�������ȥclass����Ŀ����⣬���г�Ա����string�Ĺ������������Ҫ����Ķ��⿪��

    //��ǰ���ò�������ѣ�������ͨ������������ֵ���ݣ�����ȴ�ں����ڲ����޸ġ�
}
void Cl20_test03(){
    //���ô���
    Cl20_Count = 0;
    Cl20_Student sPlato;
    bool platoIsOK = validateSutdent03(sPlato);
    std::cout<<"Cl20_Count:"<<Cl20_Count<<"\n";

    //Cl20_Count = 2
    //��test02����Ч��һ����ͬʱҲ��֤�Ķ��󲻿ɱ��޸�
}



//���ô��ݿ������������и�����
//�����и�������ϸ����:��ν���и�����ǵ�һ���������ͨ��ֵ���ݸ��������
//�������Ŀ������캯���������ã�Ҳ����˵��ʱ������������󿽱�������һ���������
//�ö���ʧȥ��������������ԣ��˻�������ȫ�Ļ���������Ե���������ת������������û�ָ��,���󽫱��и
//��2:�����и���������
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
    //ֵ���ݷ��������и������������ȫ��ʧ��ֻ�����������ԡ�
    WindowWithScrollBars wsb1;
    printNameAndDisplay01(wsb1);

    //���ô��ݣ��������������и�
    printNameAndDisplay02(wsb1);

    //ָ�봫�ݣ��������������и�.�������������Ե��Ա���
    printNameAndDisplay03(dynamic_cast<Cl20_Window *>(&wsb1));

    //��ʵ������������ָ�����ʽʵ�ֳ����ģ���˴�������ͨ����ζ�Ŵ��ݵ���ָ�롣
    //�������͵�ֵ����Ч��Ҫ�����ô���Ҫ��
}

/*�ص��ס:
 * 1.�þ�����pass-by-reference-const����py-by-value.ǰ��ͨ���Ƚϸ�Ч�����ɱ����и����⡣
 * 2.���Ϲ��򲢲���������������(��ints,chars�ȵ�)���Լ�STL�ĵ������ͺ������󡣶����Ƕ���
 *����pass-by-value�����Ƚ��ʵ�
 */

#endif //EFFECTIVECPP_CLAUSE20_PREFER_PASS_BY_REF_CONST_TO_PASS_BY_VALUE_HPP
