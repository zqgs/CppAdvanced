//
// Created by Sea on 2021/9/10.
//

#ifndef EFFECTIVECPP_CLAUSE37_NEVER_REDEFINE_FUN_INHERITED_DEFAULT_PARAM_VALUE_HPP
#define EFFECTIVECPP_CLAUSE37_NEVER_REDEFINE_FUN_INHERITED_DEFAULT_PARAM_VALUE_HPP

#include <iostream>
//����37���������¶���̳ж�����ȱʡ����ֵ
//ֱ�ӿ�����1:ֻ�ܹ��̳����ֺ���:virtual��non-virtual(���ɱ���������д),���ۼ̳�һ������ȱʡ����ֵ��virtual
class Cl37_Shape{
public:
    enum ShapeColor{Red,Green,Blue};
    virtual void draw(ShapeColor color = Red)const =0;
};
//������1:
class Cl37_Rectangle: public Cl37_Shape{
public:
    //ע��:���費ͬ��ȱʡ����ֵ��
    void draw(ShapeColor color = Green)const override{
        std::cout<<"Cl37_Rectangle::color:"<<color<<std::endl;
    }
};
class  Cl37_Circle: public Cl37_Shape{
public:
    void draw(ShapeColor color) const override{
        std::cout<<"Cl37_Circle::color:"<<color<<std::endl;
        /*  �����ô��д����������������Զ�����ô˺�����һ��Ҫָ������ֵ��
         *��Ϊ��̬������ô����������Base�̳�ȱʡ����ֵ
         *  �������ָ��(Reference)���ô˺��������Բ�ָ������ֵ
         *��Ϊ��̬��������������Base�̳�ȱʡ����ֵ
        */
    }
};

void Cl37_test01()
{
    //��̬��:��Base�̳�ȱʡ����ֵ
    Cl37_Shape* ps;
    Cl37_Shape* ps1 = new Cl37_Rectangle();
    delete ps1;
    Cl37_Shape* pr = new Cl37_Circle();
    pr->draw();
    delete pr;
    //��̬��:������Base�̳�ȱʡ����ֵ
    Cl37_Rectangle cPs;
    cPs.draw();

    Cl37_Circle cPr;
    cPr.draw(Cl37_Shape::Green);

    //������󶨷�ʽ��һ����������ȱʡֵ�ͻᷢ���仯�������������������ȫ����ΪC++Ϊ��ִ���ٶȺͱ�������ʵ��������ȡ�ᡣ
}

//����2:���������ͼ����ʵʵ�ļ̳л����ȱʡ����ֵ���ֻᷢ��ʲô��
class Cl37_Rectangle_Exp1: public Cl37_Shape{
public:
    //���ִ����ظ��������������ԡ����Shape�ڵ�ȱʡ����ֵ�ı��ˣ������ظ�����ȱʡ����ֵ����Щ������ҲҪ���Ÿı䡣
    void draw(ShapeColor color = Red)const override{
        std::cout<<"Cl37_Rectangle_Exp1::color:"<<color<<std::endl;
    }
};

//����3:Ϊ�˽������2������1�����⣬��������35�е�NVI(non-virtual-interface)����ַ�
class Cl37_Shape_Nvi{
public:
    enum ShapeColor{Red,Green,Blue};
    void draw(ShapeColor color = Red) const{
        std::cout<<"Cl37_Shape_Nvi::draw"<<std::endl;
        doDraw(color);
    }

private:
    virtual void doDraw(ShapeColor color)const =0;
};

class Cl37_Rectangle_Nvi: public Cl37_Shape_Nvi{
private:
    void doDraw(ShapeColor color)const override
    {
        std::cout<<"Cl37_Rectangle_Nvi::color:"<<color<<std::endl;
    }
};
class Cl37_Circle_Nvi: public Cl37_Shape_Nvi{
private:
    void doDraw(ShapeColor color)const override
    {
        std::cout<<"Cl37_Circle_Nvi::color:"<<color<<std::endl;
    }
};

void Cl37_test02()
{
    //�����Ǿ�̬�󶨻��Ƕ�̬��,��ʲôɫ����ʲôɫ������������ǻ���ɫ
    Cl37_Shape_Nvi* ps;
    Cl37_Shape_Nvi* ps1 = new Cl37_Rectangle_Nvi();
    delete ps1;
    Cl37_Shape_Nvi* pr = new Cl37_Circle_Nvi();
    pr->draw();
    delete pr;

    Cl37_Rectangle_Nvi cPs;
    cPs.draw();

    Cl37_Circle_Nvi cPr;
    cPr.draw(Cl37_Shape_Nvi::Green);
}

/*�ص��ס:
 *  1.���Բ�Ҫ���¶���һ���̳ж�����ȱʡ����ֵ����Ϊȱʡ����ֵ���Ǿ�̬�󶨣�
 * ��virtual������ΨһӦ�ø�д�Ķ���ȴ�Ƕ�̬��
 */




#endif //EFFECTIVECPP_CLAUSE37_NEVER_REDEFINE_FUN_INHERITED_DEFAULT_PARAM_VALUE_HPP
