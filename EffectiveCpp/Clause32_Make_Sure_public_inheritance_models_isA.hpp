//
// Created by Sea on 2021/8/31.
//

#ifndef EFFECTIVECPP_CLAUSE32_MAKE_SURE_PUBLIC_INHERITANCE_MODELS_ISA_HPP
#define EFFECTIVECPP_CLAUSE32_MAKE_SURE_PUBLIC_INHERITANCE_MODELS_ISA_HPP

#include <iostream>
#include <string>
#include <assert.h>
//����32:ȷ��public�̳���ģ��is-a��ϵ

//���class Derived��public��ʽ�̳�class Base,��ô�������ͻ���Ϊÿһ������Derived�Ķ���ͬʱҲ������ΪBase�Ķ���
//������֪ÿ��ѧ��(Derived)������(Base),��ÿ���˲�������ѧ����

//����1��
class Cl32_Bird{
public:
    virtual void fly();//����Է�
};
class Cl32_Penguin://�����һ����,���̳�����ķ������ԣ�����������ʹ�õķ���,�ǲ������
        public Cl32_Bird{
};

//����2:
class Cl32_Bird_exp1{
    //δ����fly����
};
class Cl32_FlyingBird: //����
        public Cl32_Bird_exp1{
public:
    virtual void fly();
};
class Cl32_Penguin_exp1:
        public Cl32_FlyingBird{
    //�˼̳���ϵ�����ϳ���,����������ȫ����Ӧ���г���.�����ǰϵͳֻ���ķ���֮����£���ô����1��˫�̳���ϵ����ȫ�ܹ�ʤ�Ρ�
};

//����3:�����񶼻�ɣ���������Ǵ���ġ������������ڲŻ����
void Cl32_error(const std::string& errMsg ){std::cout<<errMsg<<std::endl;}
class Cl32_Penguin_exp2:
        public Cl32_Bird{
public:
    virtual void fly(){Cl32_error("Attempt to make a penguin fly");}
};

//����4:���߸����ˣ�ֱ�Ӳ�����fly���� �����Ǳ����ڻ���⡣�����ܰѴ���������ǰ�������ڣ��ȵ�ϵͳ��ʽ�����������������ܻ��������鷳
class Cl32_Penguin_exp3:
        public Cl32_Bird_exp1{
    //������fly����,ֱ�Ӿܾ���������ʹ�õ��뷨
};


//����5:C++public�̳�,��һ�����κ������εĹ���
class Cl32_Rectangle{
public:
    virtual void setHeight(int newHeight){theHeight = newHeight;}
    virtual void setWidth(int newWidth){theWidth = newWidth;}
    virtual int height()const {return theHeight;}
    virtual int width() const{return theWidth;}
private:
    int theHeight ;
    int theWidth;
};

class Cl32_Square:
        public Cl32_Rectangle{
public:
    Cl32_Square(){}
    ~Cl32_Square(){}
};
void makeBigger(Cl32_Rectangle& r){
    int oldHeight = r.height();
    r.setWidth(r.width()+10);
    assert(r.height() == oldHeight);
}

void Cl32_test01(){
    Cl32_Square s;
    s.setWidth(10);
    s.setHeight(10);
    std::cout<<"s.width():"<<s.width()<<"\n";
    std::cout<<"s.height():"<<s.height()<<"\n";
    assert(s.width()==s.height());
    makeBigger(s);//�ı���
    assert(s.width()==s.height());//������������εĿ�߾�Ȼ����
}

//C++public�̳�����:�ܹ�ʩ����base class�������ϵ�ÿ�����飬Ҳ����ʩ����derived class���ϡ���������������C++���������ᱨ�������򲢲�һ��������ȷ��


/*�ص��ס:
 *  1."public�̳�"��ζ��is-a��������base classes���ϵ�ÿһ������һ��������derived class���ϡ���Ϊÿһ��derived class������һ��
 *base class����
 */


#endif //EFFECTIVECPP_CLAUSE32_MAKE_SURE_PUBLIC_INHERITANCE_MODELS_ISA_HPP
