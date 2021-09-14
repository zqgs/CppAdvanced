//
// Created by Sea on 2021/9/13.
//

#ifndef EFFECTIVECPP_CLAUSE39_USE_PRIVATE_INHERITANCE_JUDICIOUSLY_HPP
#define EFFECTIVECPP_CLAUSE39_USE_PRIVATE_INHERITANCE_JUDICIOUSLY_HPP

#include <iostream>

//����39:���Ƕ�������ʹ��private�̳�
//������֪:public��is-a,����һ��ѧ��(derive)�̳���(base),ѧ��������ʵ��һ�����˵���Ϊ����Ҫʱ�̻Ὣderive����ת��Ϊbase��
//��1����ô��public����private�ᷢ��ʲô��
class Cl39_Person{};
class Cl39_Student: private Cl39_Person{};

void Cl39_eat(const Cl39_Person& p){}
void Cl39_study(const Cl39_Student& s){}

void Cl39_test01()
{
    Cl39_Person p;
    Cl39_Student s;
    Cl39_eat(p);
    //Cl39_eat(s);//����,ѧ����Ȼ���ܳԶ�������Ȼprivate����is-a��ϵ��
    //֮���Ի����ʧ�ܣ�ԭ���ж�:
    //1.private�̳в��ᰵ�Խ�������ת��Ϊ���ࡣ
    //2.��private base class�̳ж��������г�Ա�����������ж�����private����ʹ��base class��ԭ����public����protected
}

//private�̳���ζ��:����ĳ��ʵ�ֳ�(D private�̳� B��ζ��D�������B����ʵ�ֶ��ã���������)
//����38�еĸ�����ʵ�����б��ֳ�����ĳ��ʵ�ֳ������ԡ�������ʹ�ø��ϣ���Ҫʱ��ʹ��private�̳�
//��ʱ���Ǳ�Ҫʹ��private�̳У�
//1.��protected��Ա��virtual����ǣ��������ʱ��
//2.���ռ䷽���������ϵ�����Ʒ�private�̳е�֧��ʱ��



//��2:��֤һ��private�̳�
class Cl39_Timer{
public:
    explicit Cl39_Timer(int tickFrequency);
    virtual void onTick() const{std::cout<<"Cl39_Timer::onTick\n";}
};
class Cl39_Widget: private Cl39_Timer{
public:
     void doSomething(){
         onTick();
     }
//���1:��д�麯��
private:
     void onTick() const override {std::cout<<"Cl39_Widget::onTick\n"};
//���2:����д�麯��
};

//��3:(����Cl39�����������ɻ���д������麯��)�������������������д������麯��,���Գ��Ը���+public�̳�
class Cl39_Widget_Exp1{
private:
    //public + ����
    class WidgetTimer: public Cl39_Timer{
    public:
        void onTick() const override {std::cout<<"Cl39_Widget_Exp1::WidgetTimer::onTick\n";}
    };
    WidgetTimer timer;
};


//�����Ƿ���Ҫ�ڴ棿
class Cl39_Empty{};//������˵��ʹ���κ��ڴ�
class Cl39_HoldAnInt{
private:
    int x;
    Cl39_Empty e;//Ӧ�ò���Ҫ�ڴ�
};
//����sizeof(Cl39_HoldAnInt)>sizeof(Cl39_Empty).���������������������������char,���������ִﲻ��1�Ĵ�С,ʵ���ֱ��Ŵ����㹻���һ��int��

//private�̳пռ�仯������Σ�
class Cl39_HoldAnInt_Exp1: private Cl39_Empty{
private:
    int x;
};
//sizeof(Cl39_HoldAnInt_Exp1) == sizeof(Cl39_Empty)����ȵġ���ʵ֤������������ʹ��private�̳У�����ʹ�ø���!!!


/*�ص��ס:
 *  1.Private�̳���ζ��(����ĳ��ʵ�ֳ�)����ͨ���ȸ��ϵļ���͡����ǵ�derived class��Ҫ���ʻ����protected�ĳ�Ա����Ҫ����
 *����̳ж�����virtual����ʱ����ô���Ҳ�Ǻ���ġ�
 *  2.�͸��ϲ�ͨ��private�̳п������empty base���Ż������������"����ߴ���С��"�ĳ���⿪�����ԣ����ܺ���Ҫ��
 */

#endif //EFFECTIVECPP_CLAUSE39_USE_PRIVATE_INHERITANCE_JUDICIOUSLY_HPP
