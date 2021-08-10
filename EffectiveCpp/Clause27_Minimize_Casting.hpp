//
// Created by Sea on 2021/8/2.
//

#ifndef EFFECTIVECPP_CLAUSE27_MINIMIZE_CASTING_HPP
#define EFFECTIVECPP_CLAUSE27_MINIMIZE_CASTING_HPP

#include <iostream>
#include <vector>
#include <memory>
//����27:��������ת�Ͷ���

//C++��������Ŀ��֮һ��:��֤"���ʹ���"�������ܷ�����

//��ʽת��(��C���)��T(expression)��(T)expression
//��ʽת��:const_cast<T>(expression)��dynamic_cast<T)(expression)��reinterpret_cast<T>(expression)��static_cast<T>(expression)
/*��ʽת�ͽ�����
 * const_castͨ��������ȥ����const�ĳ�����C++��Ψһ�д�������C++style��ת�Ͳ�����
 * dynamic_cast��Ҫ����ִ��"���°�ȫת��"��Ҳ������������ĳ�������Ƿ�����̳���ϵ�е�ĳ�����͡���ʽת���޷�ִ�еĶ�����
 *Ψһ���ܺķѾ޴�ĳɱ���ת�Ͷ���
 * reinterpret_cast��ͼִ�еͼ�ת�ͣ�ʵ�ʶ���ȡ���ڱ���������ζ�Ų�����ֲ�����罫pointer to intת��Ϊint��
 * static_cast����ǿ����ʽת�������罫non-const����תΪconst���󣬽�����ָ��תΪ������ָ��ȡ�
 */

/*��ʽת����Ȼ�Ϸ�������ʽת�͸��ܻ�ӭ:
 * 1.���Ǻ������ڴ����б���ʶ������������Լ�"�ҳ�����ϵͳ���ĸ��ص㱻�ƻ�"�Ĺ��̡�
 * 2.����ת�Ͷ�����Ŀ��Խխ��������Խ�п�����ϳ���������á�����:����ȥ��������const������ʹ��const_cast�����޷�ͨ������
 */


//����1:ʹ�þ�ʽת�͵�ʱ��
class Cl27_Widget{
public:
    explicit Cl27_Widget(int size){}
};
void Cl27_doSomeWork(const Cl27_Widget& w){}
void Cl27_test01()
{
    //��ʽת��
    Cl27_doSomeWork(Cl27_Widget(15));

    //��ʽת��
    Cl27_doSomeWork(static_cast<Cl27_Widget>(15));
}

//����2:��ʽת�������ı׶�.Ȼ�����ǲ���֪����������
class Cl27_Base{};
class Cl27_Derived: public Cl27_Base{};

void Cl27_test02()
{
    Cl27_Derived d;
    Cl27_Base* pb = &d;    //��ʽת��
    //��ʱ����������ָ���ֵ������ͬ�������ڻ���һ��ƫ����ʩ����Cl27_Derived���ϣ�����ȡ����ȷ��Baseָ��
    //��Ҫ���뽫�����ַת��Ϊchar*ָ�룬Ȼ�����������Ͻ���ָ�������������ܻᵼ�³���Ĳ���ȷ��Ϊ

    //ע��:ƫ����ֻ����ʱ��Ҫ������Ĳ��ַ�ʽ�����ǵĵ�ַ���㷽ʽ��������ı仯���仯������ָ�����Ĳ�����Ƶ�ת����
    //ĳһƽ̨�е�ͨ������ƽ̨����һ���е�ͨ��
}

//����3:����Ӧ�ÿ��Ҫ��derived���virtual��������ĵ�һ�������ȵ��û����Ӧ�ĺ���������ʵ��Ϊʲô��������
class Cl27_Window{
public:
    virtual void onResize(){std::cout<<"Cl27_Window::onResize is runing\n";}
};

class Cl27_SpecialWindow: public Cl27_Window{
public:
    virtual void onResize(){
        //��������
        //static_cast<Cl27_Window>(*this).onResize();//�����У�Ϊʲô����:��Ϊ���õĲ��ǻ����ԭʼ���󣬶��Ǳ�����������ĸ�������ĳһʱ��������෢���ı䣬��ʱ��������ȫ��֪��

        //��ȷ����
        Cl27_Window::onResize();//ֱ�ӵ��û���ԭʼ���󣬵����෢���仯��������Ҳ�����仯

        std::cout<<"Cl27_SpecialWindow::onResize is runing\n";

    }
};
void Cl27_test03()
{
    Cl27_SpecialWindow csw;
    csw.onResize();
}

/*dynamic_cast��ʹ�óɱ�:
 *  ��N����ĵ��̳���ϵ�ڵ�ĳ������ִ��dynamic_cast��ÿһ�ο��ܶ������N�ε�strcmp���ã����ԱȽ�class���ơ�
 * ��Ȼ���ؼ̳гɱ����ߡ�
 *  ֮������Ҫdynamic_cast��ͨ��������һ��������Ķ�����ִ���������������������ȴֻ��һ��baseָ��������ã�
 * ��ʱ����Ҫdynamic_cast�������������
 */

//��Ҫ����ͨ������ָ��������������������һ��������:
// һ��ʹ�������������д洢ָ��������ָ��Ķ���(ͨ��������ָ��)
//����:4 ����Cl27_Window/Cl27_SpecialWindow�̳���ϵ��ֻ��Cl27_SpecialWindow����֧����˸Ч��
class Cl27_SpecialWindowExp1: public Cl27_Window{
public:
    virtual void onResize(){
        //��������
        //static_cast<Cl27_Window>(*this).onResize();//�����У�Ϊʲô����:��Ϊ���õĲ��ǻ����ԭʼ���󣬶��Ǳ�����������ĸ�������ĳһʱ��������෢���ı䣬��ʱ��������ȫ��֪��

        //��ȷ����
        Cl27_Window::onResize();//ֱ�ӵ��û���ԭʼ���󣬵����෢���仯��������Ҳ�����仯

        std::cout<<"Cl27_SpecialWindow::onResize is runing\n";

    }

    void blink(){  std::cout<<"Cl27_SpecialWindowExp1::blink is runing\n";}
};
void Cl27_test04()
{
    //��������
    typedef std::vector<std::shared_ptr<Cl27_Window>> VPM;
    VPM winPtrs;

    for(VPM::iterator iter = winPtrs.begin();
            iter!=winPtrs.end();iter++)
    {
        if(Cl27_SpecialWindowExp1* psw = dynamic_cast<Cl27_SpecialWindowExp1*>(iter->get())){
            psw->blink();
        }
    }

    //��������:�ο��ڶ����ʵ��
    for(VPM::iterator iter = winPtrs.begin();
        iter!=winPtrs.end();iter++)
    {
        //*(iter)->blink(); //���������Ͳ�����ͬһ�����ڴ洢ָ��"ָ�����п��ܵĸ���������"
    }
}
// ����ͨ������ӿڴ���"���п��ܵĸ���window������"
class Cl27_WindowExperience{
public:
    virtual void onResize(){std::cout<<"Cl27_Window::onResize is runing\n";}
    virtual void blink(){
        //ȱʡ ֻ�����ṩ�ӿ�����
    }
};
class Cl27_SpecialWindowExperience: public Cl27_WindowExperience{
public:
    virtual void onResize(){
        //��������
        //static_cast<Cl27_Window>(*this).onResize();//�����У�Ϊʲô����:��Ϊ���õĲ��ǻ����ԭʼ���󣬶��Ǳ�����������ĸ�������ĳһʱ��������෢���ı䣬��ʱ��������ȫ��֪��

        //��ȷ����
        Cl27_WindowExperience::onResize();//ֱ�ӵ��û���ԭʼ���󣬵����෢���仯��������Ҳ�����仯

        std::cout<<"Cl27_SpecialWindow::onResize is runing\n";

    }
    void blink(){  std::cout<<"Cl27_SpecialWindowExperience::blink is runing\n";}
};

void Cl27_test05()
{
    //���һ������ָ��
    std::shared_ptr<Cl27_WindowExperience> scwe(new Cl27_SpecialWindowExperience()); //������ʽת��: Cl27_SpecialWindowExperience->Cl27_WindowExperience
    scwe->blink();//�õ�������ִ�н��
}

//����������һ����������-------ʹ��"���Ͱ�ȫ����"��"virtual�������̳���ϵ�Ϸ��ƶ�"-------�����Ǿ��ԣ���������Ӧ�ṩһ��dynamic_cast�������
////����:5 ����������ʹ��dynamic_cast:
class Cl27_WindowExp1{ virtual void onResize(){}};
class Cl27_SpecialWindowExp2 : public Cl27_WindowExp1{};
class Cl27_SpecialWindowExp3 : public Cl27_WindowExp1{};
class Cl27_SpecialWindowExp4 : public Cl27_WindowExp1{};
void Cl27_test06()
{
    //��������
    typedef std::vector<std::shared_ptr<Cl27_WindowExp1>> VPM;
    VPM winPtrs;

    for(VPM::iterator iter = winPtrs.begin();
        iter!=winPtrs.end();iter++)
    {
        if(Cl27_SpecialWindowExp2* psw = dynamic_cast<Cl27_SpecialWindowExp2*>(iter->get())){
            //...
        }
        else if(Cl27_SpecialWindowExp3* psw = dynamic_cast<Cl27_SpecialWindowExp3*>(iter->get())){
            //...
        }
        else if(Cl27_SpecialWindowExp4* psw = dynamic_cast<Cl27_SpecialWindowExp4*>(iter->get())){
            //...
        }
    }

    //���ϲ����Ĵ����ִ����������һ������ȣ�ÿ�μ̳���ϵ�����ı䣬��������������Ƿ���Ҫ�޸ġ�һ�������µ������࣬�������Ҫ�ж������µķ�֧
    //�����Ĵ���������"�����麯������"�Ķ���ȡ����֮
    //������C++�������ʹ��ת�ͣ�ʹ�õ�ʱ�����������ĳ�������ڣ������Ľӿڻᱣ�������߲��ܺ����ڲ��Ķ���Ӱ��
}

/*�ص��ס:
 * 1.������ԣ���������ת�ͣ��ر�����ע��Ч�ʵĴ����б���ʹ��dynamic_cast.����������Ҫת�Ͷ��������ŷ�չ����ת�͵�������
 * 2.���ת���Ǳ�Ҫ�ģ����Ž���������ĳ����������
 * 3.����ʹ��C++style��ת�ͣ���Ҫʹ�þ�ʽת�͡�ǰ�����׷ֱ��ҷֹ��Ƚ���ȷ
 */





#endif //EFFECTIVECPP_CLAUSE27_MINIMIZE_CASTING_HPP
