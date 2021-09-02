//
// Created by Sea on 2021/9/2.
//

#ifndef EFFECTIVECPP_CLAUSE34_DISTINGUISHING_BETWEEN_INTERFACE_INHERITANCE_AND_IMPLEMENTATION_INHERITANCE_HPP
#define EFFECTIVECPP_CLAUSE34_DISTINGUISHING_BETWEEN_INTERFACE_INHERITANCE_AND_IMPLEMENTATION_INHERITANCE_HPP

#include <iostream>
#include <string>

//����34:���ֽӿڼ̳к�ʵ�ּ̳�

//˼��:��Ϊclass����ߣ���ʱ��ϣ��������ֻ�̳г�Ա�����Ľӿڡ���ʱ��ϣ��������ͬʱ�̳к����Ľӿں�ʵ�֣�
//����ϣ���ܹ���д�������̳е�ʵ�֡���ʱ��ϣ��������ͬʱ�̳к��������Ľӿں�ʵ�֣����Ҳ�����д�κζ���

//����1:����virtual���ǳ����࣬���ܽ���ʵ����
class Cl34_Shape{
public:
    virtual void draw() const =0;//�ӿ�
    virtual void error(const std::string& msg){std::cout<<"ERROR:"<<msg<<"\n";}//�ӿ�+Ĭ��ʵ��
    int objectID() const{std::cout<<"objectID\n";return 0;}//�ӿں�ǿ��ʵ��
};
void Cl34_Shape::draw() const {
    std::cout<<"Cl34_Shape::draw\n";
}
//Cl34_Shape��һ�������࣬ʹ���߲��ܴ���ʵ�壬ֻ�ܴ���������ʵ�塣Cl34_Shapeǿ�ҵ�Ӱ������public��ʽ�̳����������ࡣ
//��Ϊ:��Ա�����Ľӿ��ܻᱻ�̳С�public��ζ��is-a,�Ի���Ϊ����κ��¶���������һ��Ϊ�档

//����Cl34_Shape�࣬������һ����:
//pure virtual(���麯��)������ͻ������:
//1.���Ǳ��뱻�κ�"�̳е�"��������������(��˼��:ֻҪ�̳е����к��д��麯��,��ô����������һ��Ҫ����ʵ��)��
//2.���麯���ڳ�������ͨ��û�ж��塣(�����ǿ�и����麯��һ��ʵ��,C++�����ᱨ�������õ�Ψһ;����ͨ��������)
//�ܽ�:����һ��pure virtual������Ŀ�ľ���Ϊ��������ֻ�̳к����ӿ�


class Cl34_Rectangle: public Cl34_Shape{
public:
    void draw() const override{std::cout<<"Cl34_Rectangle::draw\n";}
};
class Cl34_Ellipse: public Cl34_Shape{
    void draw() const override{std::cout<<"Cl34_Ellipse::draw\n";}
};

void Cl34_test01(){
    //Cl34_Shape* ps = new Cl34_Shape();//����Cl34_Shape�ǳ����
    Cl34_Shape* ps1 = new Cl34_Rectangle();
    ps1->draw();
    Cl34_Shape* ps2 = new Cl34_Ellipse();
    ps2->draw();

    ps1->Cl34_Shape::draw();
    ps2->Cl34_Shape::draw();

    delete ps1;
    delete ps2;
}

//impure virtual(�Ǵ��麯��):�봿�麯����ͬ����,����Ҫ������ǿ��ʵ��,����Ҫ�����ṩһ��ȱʡ�汾����������Զ�����д��
//����һ��impure virtual(�Ǵ��麯��)��Ŀ��:��������̳иú����Ľӿں�ȱʡʵ�֡�
//����:Cl34_Shape::error(...),�������������Լ����������������Ҫ�������������ô������д�ú���������ͻ���ĺ���һ������ôֱ��ʹ��ȱʡ�汾���ɡ�
//����2:����impure virtual����ͬʱָ������������ȱʡ��Ϊ��ȴ�п������Σ�ա�
class Cl34_Airport{
    //���Ա��ֻ���
public:
    std::string strAddress;
};
//�ɻ�
class Cl34_Airplane{
public:
    virtual void fly(const Cl34_Airport& destnation){std::cout<<"Cl34_Airplane::fly to "<<destnation.strAddress<<"\n";}
};
//A�ͺź�B�ͺŵķɻ� �� AB�ͺŵķɻ�������ͬ�ķ��з�ʽ
class Cl34_ModelA: public Cl34_Airplane{};
class Cl34_ModelB: public Cl34_Airplane{};

//��������һ���ͺ�C�ĺ��ߣ����з�ʽ��ͬ
class Cl34_ModelC: public Cl34_Airplane{
    //������Ŀ�������������¶���C�ͺŷɻ���Ҫ���еķ�ʽ,��ô�⽫�Ǹ�������
};
void Cl34_test02()
{
    Cl34_Airport PDX;//ѡ��һ������
    PDX.strAddress = "HongQiao";//����λ���Ϻ�����

    Cl34_Airplane *pa = new Cl34_ModelC();//ѡ��һ�ܷɻ�,��ָ��C�ͷɻ��е���������,��C�ķ��з�ʽ��Ĭ��ȱʡ�ķ��з�ʽ�ǲ�һ�µ�
    pa->fly(PDX);//�����˻����ȱʡ����
    delete pa;
}

//���ⲻ�ڻ���Cl34_Airplane::fly��ȱʡ��Ϊ,������Model CΪ���ṩC����д�汾,���µ����˻���ȱʡ�汾��
//����3:��α��������������:������Ҫ�ж�"virtual�����ӿ�"����"ȱʡʵ��"֮�������
class Cl34_Airplane_Exp1{
public:
    virtual void fly(const Cl34_Airport& destnation) = 0;//ѡ�ô��麯������������ǿ��ʵ�ַ��з�ʽ
};
//�ṩһ��ͨ�ð汾�ķ��з�ʽ
void Cl34_Airplane_Exp1::fly(const Cl34_Airport &destnation)
{
    std::cout<<"Cl34_Airplane::fly to "<<destnation.strAddress<<"\n";
}

//A�ͺź�B�ͺŵķɻ� �� AB�ͺŵķɻ�������ͬ�ķ��з�ʽ
class Cl34_ModelA_exp1: public Cl34_Airplane_Exp1{
public:
    void fly(const Cl34_Airport& destnation) override{
        Cl34_Airplane_Exp1::fly(destnation);//���û����ͨ�ð汾
    }
};
class Cl34_ModelB_exp1: public Cl34_Airplane_Exp1{
public:
    void fly(const Cl34_Airport& destnation) override{
        Cl34_Airplane_Exp1::fly(destnation);//���û����ͨ�ð汾
    }
};
//������һ���ͺ�C�ķɻ������з�ʽ��ͬ
class Cl34_ModelC_exp1: public Cl34_Airplane_Exp1{
public:
    void fly(const Cl34_Airport& destnation) override{
        std::cout<<"Cl34_ModelC_exp1::fly to "<<destnation.strAddress<<"\n";
    }
};
void Cl34_test03()
{
    Cl34_Airport PDX;//ѡ��һ������
    PDX.strAddress = "PuDong";//����λ���Ϻ��ֶ�

    Cl34_Airplane_Exp1 *pa = new Cl34_ModelC_exp1();//ѡ��һ�ܷɻ�,��ָ��C�ͷɻ��е���������
    pa->fly(PDX);//���÷�ʽ������2������һ��,ȴʵ��ʵѡ�������ȷ�ķ��з�ʽ����л���麯���Ĺ���
    delete pa;
}


//  �������non-virtual(���麯��):�������еĺ��������麯��ʱ,��ζ�Ų�ϣ�������൮������಻ͬ�İ汾���κ������඼��Ӧ�ó��Ըı�����Ϊ������non-virtual
//�������������ʱ��������������ԣ��������������������������¶��塣
//����һ��non-virtual(���麯��)��Ŀ��:Ϊ����������̳к����Ľӿں�һ��ǿ���Ե�ʵ�֡�


//  �ܽ�:pure virtual������impure virtual������non-virtual����֮��Ĳ��죬�ֱ������������Ҫ�̳еĶ���:ֻ�̳нӿڣ����Ǽ̳нӿں�һ��ȱʡʵ�֣�
//���Ǽ̳нӿں�һ��ǿ��ʵ�֡�

//  �����Ĵ���(��������):1.�����г�Ա����������Ϊnon-virtual����,��ʹ��������û��ʣ��ռ�����ػ�������������������һ������Ļ�����non-virtual���Ǻ���ġ�
//2.�����еĳ�Ա����������Ϊvirtual��������ʱ����ȷ��(����:����31��interface class),Ȼ���󲿷�ʱ��ĳЩ�����Ͳ������������б����¶��塣

/*�ص��ס:
 *  1.�ӿڼ̳к�ʵ�ּ̳в�ͨ����public�̳��£����������Ǽ̳л���Ľӿ�
 *  2.pure virtual���麯��ֻ����ָ���ӿڼ̳�
 *  3.impure virtual �Ǵ��麯������ָ���ӿڼ̳м�ȱʡʵ�ּ̳�
 *  4.non-virtual���麯������ָ���ӿ��Լ�ǿ����ʵ�ּ̳�
 */






#endif //EFFECTIVECPP_CLAUSE34_DISTINGUISHING_BETWEEN_INTERFACE_INHERITANCE_AND_IMPLEMENTATION_INHERITANCE_HPP
