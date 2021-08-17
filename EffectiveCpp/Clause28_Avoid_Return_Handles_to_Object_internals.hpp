//
// Created by Sea on 2021/8/17.
//

#ifndef EFFECTIVECPP_CLAUSE28_AVOID_RETURN_HANDLES_TO_OBJECT_INTERNALS_HPP
#define EFFECTIVECPP_CLAUSE28_AVOID_RETURN_HANDLES_TO_OBJECT_INTERNALS_HPP

#include <memory>
#include <iostream>
//����28:���ⷵ��handlesָ������ڲ��ɷ�


//ֱ������һ������ʾ��1��
//��һ�����ʾ������
class Cl28_Point{
public:
    Cl28_Point(){}
    Cl28_Point(int x,int y):_x(x),_y(y){
        std::cout<<"Cl28_Point:X->"<<_x<<"\n";
        std::cout<<"Cl28_Point:Y->"<<_x<<"\n";
    }
    ~Cl28_Point(){}

    void setX(int value){_x = value;std::cout<<"Cl28_Point:X->"<<_x<<"\n";}
    void setY(int value){_y = value;std::cout<<"Cl28_Point:Y->"<<_y<<"\n";}
private:
    int _x;
    int _y;
};

//��һ���ṹ���ʾ����
struct Cl28_RectData{
    Cl28_RectData(Cl28_Point u,Cl28_Point l):ulhc(u),lrhc(l){}
    Cl28_Point ulhc;//���Ͻ�
    Cl28_Point lrhc;//���½�
};
//����һ��������
class Cl28_Rectangle{
public:
    Cl28_Rectangle(Cl28_Point u,Cl28_Point l){
        pData = std::make_shared<Cl28_RectData>(u,l);
    }
    Cl28_Point& upperLet() const{return pData->ulhc;}
    Cl28_Point& lowerRighe() const{return pData->lrhc;}
private:
    std::shared_ptr<Cl28_RectData> pData;
};
//�������������
void Cl28_test01()
{
    Cl28_Point coord1(0,0);
    Cl28_Point coord2(100,100);

    const Cl28_Rectangle rec(coord1,coord2);
    rec.upperLet().setX(50);//ǿ���޸��ڲ���ֵ�������rec��const���ɱ�ģ�ȴ��ǿ���޸����ڲ�����
}
//��������Ӳ�������������:
//1.��Ա�����ķ�װ�����ֻ����"������reference"�ĺ������ʼ�����Ȼulhc��lrhc��������δprivate��ʵ������public����Ϊpublic�������������ǵ�����
//2.���const��Ա��������һ��reference������ָ���������������й����������ֱ��洢�ڶ���֮�⣬��ô������������߿����޸��������

//���淢�������鶼������"��Ա��������reference"��������ص���ָ������������ͬ��������ɷ��������á�ָ�롢������������ν��"handles",����һ������
//�ڲ����ݵ�handle��ͬʱ��Ҳ��"���Ͷ����װ��"��

//�����������������ʾ��2:ֻ��Ҫ�������ͼ���const����
class Cl28_RectangleExp1{
public:
    Cl28_RectangleExp1(Cl28_Point u,Cl28_Point l){
        pData = std::make_shared<Cl28_RectData>(u,l);
    }
    const Cl28_Point& upperLet() const{return pData->ulhc;}
    const Cl28_Point& lowerRighe() const{return pData->lrhc;}
private:
    std::shared_ptr<Cl28_RectData> pData;
};
void Cl28_test02()
{
    Cl28_Point coord1(0,0);
    Cl28_Point coord2(100,100);

    const Cl28_RectangleExp1 rec(coord1,coord2);
    //rec.upperLet().setX(50);//ǿ���޸��ڲ���ֵ��������ֱ�ӱ���
}
//�������upperLet��lowerRighe���Ƿ�����ָ���ڲ���handles�����ܻᵼ�¶��ָ��ָ��ͬһ��handle����ĳһ��handle���ͷź󣬵���"dangling handle"(�վ��:
// ��ָ�Ķ����������ڣ��������Դ���Ǻ�������ֵ)

//����һ��ʾ��3��
class Cl28_GUIObject{};
const Cl28_RectangleExp1 boundingBox(const Cl28_GUIObject& obj)
{
    Cl28_Point coord1(0,0);
    Cl28_Point coord2(100,100);

    const Cl28_RectangleExp1 rec(coord1,coord2);
    return rec;
    //����һ��Cl28_RectangleExp1����,����������rec�������٣���ӵ���Point����
}
void Cl28_test03()
{
    Cl28_GUIObject * pgo;
    //pUpperLeft���ܻ��ɿվ���������ټ������û������ڴ�й©
    const Cl28_Point* pUpperLeft = &(boundingBox(*pgo).upperLet());
}

//������ζ�Ų��ܷ���handle����ʱ�������ô��������:operator[]�������ȡstring��vertor�ĸ���Ԫ�أ���Щ���ݻ��������������ٶ�����

/*�ص��ס:
 * 1.���ⷵ��handle(����reference��ָ�롢������)ָ������ڲ��������������ӷ�װ�ԣ�����const��Ա��������Ϊ����const��
 * ���ѿվ��(dangling handle)�Ŀ����Խ������.
 */



#endif //EFFECTIVECPP_CLAUSE28_AVOID_RETURN_HANDLES_TO_OBJECT_INTERNALS_HPP
