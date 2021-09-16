//
// Created by Sea on 2021/9/16.
//

#ifndef EFFECTIVECPP_CLAUSE42_UNDERSTAND_THE_TWO_MEANINGS_OF_TYPENAME_HPP
#define EFFECTIVECPP_CLAUSE42_UNDERSTAND_THE_TWO_MEANINGS_OF_TYPENAME_HPP

#include <iostream>

//����42:�˽�typename��˫������

//��:��template����ʽ�У�class��typename��ʲô��ͬ��
//��:û�в�ͬ��������template���Ͳ���ʱ��class��typename��������ȫ��ͬ��

//����1:��Щʱ������ʹ��typename����������:
template <typename C>
void
Cl42_print2nd(const C& container)
{
    if(container.size()>=2)
    {
       // C::const_itertor iter(container.begin());//���ֱ��뱨���ˡ�����ԭ��:����C::const_itertor��һ�����͵�ʱ��������ʽ�Ż�ɹ���C++�ƶϳ�C::const_itertor�п��ܲ������͡�
       //����Ҫ��ô�����أ�ʹ��typenameǿ��ָ��C::const_itertorʱһ�����͡�
        typename C::const_itertor iter(container.begin());
        ++iter;
        int value = *iter;
        std::cout<<value<<"\n";
    }
}
//template������������template�����������Ƴ�Ϊ"��������"��
//��C::const_itertor����Ƕ��״�������Ƴ�Ϊ"Ƕ�״�������"��
//��int���������κ�template���������ƣ������Ƴ�Ϊ"ν�Ǵ�������"��
//C++һ���Թ���:�κ���Ҫ��template��ָ���Ƕ�״����������ƣ��ͱ����������ʽǰʹ��typename�ؼ��֡�


//����2:typenameֻ����������Ƕ�״����������ƣ��������Ʋ���ʹ������
template <typename T>//����ʹ��"typename"(��"class")
void
Cl42_fun
(
        const T& container,//������ʹ��"typename"
        typename  T::itertor iter//һ��Ҫʹ��"typename"
){}

//"typename������ΪǶ�״����������Ƶ�ǰ׺��"��һ�����������:
//1.typename�����Գ�����base class list�ڵ�Ƕ�״�����������֮ǰ��
//2.typenameҲ�����Գ����ڳ�Ա��ֵ������Ϊbase class�����η���
//����3:
template<typename T>
class Cl42_Base{};

template<typename T>
class Cl42_Derived: public Cl42_Base<T>::Nested{//base list�в��������typename
public:
    explicit Cl42_Derived(int x): Cl42_Base<T>::Nested(x)//��Ա��ֵ�в��������typename
    {
        typename  Cl42_Base<T>::Nested temp;//�Ȳ���base class listҲ���ڳ�Ա��ֵ���У���Ҫʹ��typename
    }
};

//����4:����һ��typedef��typename��ʹ��
template<typename IterT>
void workWithItertor(IterT& iter)
{
    typedef typename std::iterator_traits<IterT>::value_type value_temp ;//��Ϊstd::iterator_traitsҲ��Ƕ�״������ƣ����Ա���ʹ��typename�ؼ���
    value_temp  temp(*iter);
}

/*�ص��ס:
 *  1.����template����ʱ,ǰ׺�ؼ���class��typename���Ի�����
 *  2.��ʹ�ùؼ���typename��ʶǶ�״�������;��������base class list(������)��member initialization list(��Ա��ֵ��)����typename��Ϊ���η�
 */


#endif //EFFECTIVECPP_CLAUSE42_UNDERSTAND_THE_TWO_MEANINGS_OF_TYPENAME_HPP
