//
// Created by Sea on 2021/9/23.
//

#ifndef EFFECTIVECPP_CLAUSE45_USE_MEMBER_FUN_TEMPLATE_TO_ACCEPT_ALL_COMPATIBLE_TYPES_HPP
#define EFFECTIVECPP_CLAUSE45_USE_MEMBER_FUN_TEMPLATE_TO_ACCEPT_ALL_COMPATIBLE_TYPES_HPP

#include <iostream>
#include <memory>
//����45:���ó�Ա����ģ��������м�������
//����ָ��:��ָ"��Ϊ��ָ��"�Ķ��󣬲��ṩָ��û�еĻ��ܡ�

//����1:��ʵָ���ǿ���֧����ʽת���ġ�
class Cl45_Top{
public:
    virtual void print_top(){std::cout<<"Cl45_Top\n";}
};
class Cl45_Middle: public Cl45_Top{
public:
     void print_top(){std::cout<<"Cl45_Middle\n";}
};
class Cl45_Bottom: public Cl45_Middle{
public:
    void print_top(){std::cout<<"Cl45_Bottom\n";}
};

void Cl45_test01()
{
    Cl45_Top* pt1 = new Cl45_Middle();
    pt1->print_top();

    Cl45_Top* pt2 = new Cl45_Bottom();
    pt2->print_top();

    const Cl45_Top* pct2 = pt1;
}

//����2:������Զ�������ָ���������ת��������΢���е��鷳
template<typename T>
class Cl45_SmartPtr{
public:
    Cl45_SmartPtr
    (T* readPtr)
    {
        tPtr = readPtr;
    }
    Cl45_SmartPtr& operator=(const Cl45_SmartPtr& rhs)
    {
        if (this != &rhs)
        {
            this->tPtr = rhs.tPtr;
        }
        return *this;
    }

private:
    T* tPtr;
};

void Cl45_test02()
{
    //Cl45_SmartPtr<Cl45_Top> pt1 = Cl45_SmartPtr<Cl45_Middle>(new Cl45_Middle());
    //Cl45_SmartPtr<Cl45_Top> pt1 = Cl45_SmartPtr<Cl45_Bottom>(new Cl45_Bottom());
    //���������������Ǳ���ġ�ԭ����:��ͬtemplate�����������������������������Ϊ��ȫ��ͬ��class��
}

//�������ܱ�дͨ�ù���������������ָ����?
//ֱ�ۿ���Ӧ����Cl45_SmartPtr<Cl45_Middle>��Cl45_SmartPtr<Cl45_Bottom>�����һ��Cl45_SmartPtr<Cl45_Top>�����Ĺ��캯����
//����պ��������䣬Cl45_SmartPtr<Cl45_Top>�����ֱ��������������ָ�빹���Լ���

//��ˣ���ԭ����ԣ�������Ҫ�Ĺ��캯����û��ֹ������Ϊһ��template���Ա��������ľ��ֻ�������������������������������ǲ���Ϊ��Cl45_SmartPtr<Cl45_Top>д
//һ�����캯��������Ϊ��дһ������ģ�壬������ģ���֮Ϊmember function template(��Ա����ģ��),��������Ϊclass���ɺ�����

//����3:��������ʵ��
template <typename T>
class Cl45_SmartPtr_Exp{
public:
    Cl45_SmartPtr_Exp() = default;
    Cl45_SmartPtr_Exp(T* readPtr)
    {
        tHeldPtr = readPtr;
    }
    ~Cl45_SmartPtr_Exp()
    {
        std::cout << "Cl45_SmartPtr_Exp:Destructo" << std::endl;
    }

    template<typename U>
    Cl45_SmartPtr_Exp(const Cl45_SmartPtr_Exp<U>& readPtr)://ʡ��explicit��Ϊ��֧����ʽת��
    //ʹ�ó�Ա��ֵ������ʼ��Cl45_SmartPtr_Exp<T>֮������ΪT�ĳ�Ա��������������ΪU*��ָ����Ϊ��ֵ��
    //������Ϊֻ�е�"����ĳ����ʽת���ɽ�һ��U*ָ��תΪT*ָ��"ʱ����ͨ�����롣
    tHeldPtr(readPtr.get())

    {std::cout << "Cl45_SmartPtr_Exp:CopyConstructor" << std::endl;}
    T* get() const{return tHeldPtr;}

public:
    void Call(){tHeldPtr->print_top();}
private:
    T* tHeldPtr;
};
void Cl45_test03()
{
    Cl45_SmartPtr_Exp<Cl45_Middle> spd(new Cl45_Middle());
    Cl45_SmartPtr_Exp<Cl45_Top> spb(spd);
}

//member function template(��Ա����ģ��)��Ч�ò������ڹ��캯����Ҳ������֧�ָ�ֵ��������:share_ptr�������Լ��ݵ�����ָ���Լ���weak_ptr֮��ĸ�ֵ������
//����4:����һ��share_ptr��ʵ��
template <typename T>
class Cl45_Shareptr{
public:
    //����
    template<typename Y>
    explicit Cl45_Shareptr(Y* p){}//����ָ��
    template<typename Y>
    explicit Cl45_Shareptr(std::shared_ptr<Y> const& p){}//shared_ptrָ��
    template<typename Y>
    explicit Cl45_Shareptr(std::weak_ptr<Y> const& p){}//weak_ptrָ��
    template<typename Y>
    explicit Cl45_Shareptr(std::auto_ptr<Y> const& p){}//auto_ptrָ��

    //��ֵ
    template<typename Y>
    Cl45_Shareptr& operator=(std::shared_ptr<Y> const& r){}
    template<typename Y>
    Cl45_Shareptr& operator=(std::auto_ptr<Y> const& r){}
};

//���Ϲ��캯��������ʽ�ģ�����"����copy���캯������"��
//member function template(��Ա����ģ��)�Ǹ�����Ķ������������ǲ����ı����Ի�����������05��������������Ϊ��������4��������
//std::share_ptr������һ������copy���죬һ������T��Y��ͬ�������������캯���ᱻ���ֻ�Ϊ"�����Ŀ������캯��"����ô�������Ƿ�ᰵ������һ��copy���캯���أ�
//��ĳ��share_ptr���������һ��ͬ��share_ptr����չ������ʱ���������Ὣ"�����������캯��ģ��"���ֻ���

//�ص��ס:��Ա��������ı����Թ������������Ҫһ���������캯������ȴû����������ô�������ᰵ������һ����
//��class�����������Ŀ������캯����������֯�����������Լ��Ŀ������캯�������������Ҫ����copy�ķ������棬��ô�����ͬʱ���������ͷǷ���������


/*�ص��ס:
 *  1.��ʹ��member function template(��Ա����ģ��)����"�ɽ���������������"�ĺ�����
 *  2.�������member����"����copy����"��"������ֵ����"��������Ҫ����������copy���캯����copy��ֵ��������
 */

#endif //EFFECTIVECPP_CLAUSE45_USE_MEMBER_FUN_TEMPLATE_TO_ACCEPT_ALL_COMPATIBLE_TYPES_HPP
