//
// Created by Sea on 2021/9/10.
//

#ifndef EFFECTIVECPP_CLAUSE38_MODEL_HAS_A_IS_IMPLEMENTED_IN_TERMS_OF_THROUGH_COMPOSITION_HPP
#define EFFECTIVECPP_CLAUSE38_MODEL_HAS_A_IS_IMPLEMENTED_IN_TERMS_OF_THROUGH_COMPOSITION_HPP

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

//����38:ͨ��������ģ��has-a��"����ĳ��ʵ�ֳ�"

//����(composition)ʽ����֮���һ�ֹ�ϵ,��ĳ�����͵Ķ����ں��������͵Ķ��󣬱��Ǹ��ϡ�
//����1:����
class Cl38_Address {/*...*/};
class Cl38_PhoneNumber {/*...*/};
class Cl38_Person{
private:
    std::string name;//�ϳɳɷ�1
    Cl38_Address address;//�ϳɳɷ�2
    Cl38_PhoneNumber voiceNumber;//�ϳɳɷ�3
    Cl38_PhoneNumber faxNumber;//�ϳɳɷ�4
};
//����������и��ϵ�ͬ���:�ֲ㣨layering�����ں���containment�����ۺϣ�aggregation������Ƕ��embedding��
//"public�̳�"��is-a,������ζ��has-a(��һ��/����ĳ��ʵ�ֳ�)
//����������:�������ˡ�һ������Ƶ��������Ӧ����ϸ��ʵ��:��������������������������ʵ����
//�����Ϸ�����Ӧ����ʱ�����ֳ�has-a��ϵ�������Ϸ�����ʵ����ʱ�����ֳ�����ĳ��ʵ�ֳ����ԡ�


//ʵ��һ��Set������Set��list����,ȴ������ʹ��is-a���
template <class T>
class Cl38_Sets: public  std::list<T>{};//Ϊʲô������ʹ��is-a�����أ���:is-a��ʾ������Ϊ����¶��ڻ���Ҳһ��Ϊ�棬��Set�����������ͬԪ��,��listȴ���ԡ�

//��has-aʵ��һ��Set����(���Ǻ����,��set��ע��Ч��)��Set��list����,�󲿷ֻ��ܿ�������list��ʵ��
template<class T>
class Cl38_Sets1{
public:
    bool member(const T& item)const
    {
        return std::find(rep.begin(),rep.end(),item)!=rep.end();
    }
    void insert(const T& item)
    {
        if(!member(item)) rep.push_back(item);
    }
    void remove(const T& item)
    {
        typename std::list<T>::iterator it =  std::find(rep.begin(),rep.end(),item);
        if(it!=rep.end())
            rep.erase(item);
    }
    std::size_t size()const
    {
        return rep.size();
    }
    void print()
    {
        std::for_each(rep.begin(),rep.end(),[](const T& n){
            std::cout<<n<<std::endl;
        });
    }
private:
    std::list<T> rep;

};

void Cl38_test01()
{
    Cl38_Sets1<int> _set;
    _set.insert(5);
    _set.insert(5);
    _set.print();
}
/*�ص��ס:
 *  1.����(composition)�������public�̳���ȫ��ͬ��
 *  2.��Ӧ����(application domain),������ζ��has-a(��һ��������:����סַ��)����ʵ���򣬸�����ζ�Ÿ���ĳ��ʵ�ֳ���
 */

#endif //EFFECTIVECPP_CLAUSE38_MODEL_HAS_A_IS_IMPLEMENTED_IN_TERMS_OF_THROUGH_COMPOSITION_HPP
