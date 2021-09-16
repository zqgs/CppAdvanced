//
// Created by Sea on 2021/9/16.
//

#ifndef EFFECTIVECPP_CLAUSE42_UNDERSTAND_THE_TWO_MEANINGS_OF_TYPENAME_HPP
#define EFFECTIVECPP_CLAUSE42_UNDERSTAND_THE_TWO_MEANINGS_OF_TYPENAME_HPP

#include <iostream>

//条款42:了解typename的双重意义

//问:在template声明式中，class和typename有什么不同？
//答:没有不同。当声明template类型参数时，class和typename的意义完全相同。

//例子1:有些时候必须得使用typename。不信来看:
template <typename C>
void
Cl42_print2nd(const C& container)
{
    if(container.size()>=2)
    {
       // C::const_itertor iter(container.begin());//发现编译报错了。报错原因:这里C::const_itertor是一个类型的时候，这个表达式才会成功。C++推断出C::const_itertor有可能不是类型。
       //我们要怎么做了呢？使用typename强制指定C::const_itertor时一个类型。
        typename C::const_itertor iter(container.begin());
        ++iter;
        int value = *iter;
        std::cout<<value<<"\n";
    }
}
//template内名称相依于template参数，该名称称为"从属名称"。
//像C::const_itertor这类嵌套状，该名称称为"嵌套从属名称"。
//像int并补依赖任何template参数的名称，该名称称为"谓非从属名称"。
//C++一般性规则:任何想要在template中指涉个嵌套从属类型名称，就必须在它表达式前使用typename关键字。


//例子2:typename只被用来验明嵌套从属类型名称，其他名称不该使用它。
template <typename T>//允许使用"typename"(或"class")
void
Cl42_fun
(
        const T& container,//不允许使用"typename"
        typename  T::itertor iter//一定要使用"typename"
){}

//"typename必须作为嵌套从属类型名称的前缀词"这一规则例外的是:
//1.typename不可以出现在base class list内的嵌套从属类型名称之前。
//2.typename也不可以出现在成员初值列中作为base class的修饰符。
//例子3:
template<typename T>
class Cl42_Base{};

template<typename T>
class Cl42_Derived: public Cl42_Base<T>::Nested{//base list中不允许出现typename
public:
    explicit Cl42_Derived(int x): Cl42_Base<T>::Nested(x)//成员初值列不允许出现typename
    {
        typename  Cl42_Base<T>::Nested temp;//既不在base class list也不在成员初值列中，需要使用typename
    }
};

//例子4:来看一下typedef和typename的使用
template<typename IterT>
void workWithItertor(IterT& iter)
{
    typedef typename std::iterator_traits<IterT>::value_type value_temp ;//因为std::iterator_traits也是嵌套从属名称，所以必须使用typename关键字
    value_temp  temp(*iter);
}

/*重点记住:
 *  1.声明template参数时,前缀关键字class和typename可以互换。
 *  2.请使用关键字typename标识嵌套从属名称;但不得在base class list(基类列)或member initialization list(成员初值列)内以typename作为修饰符
 */


#endif //EFFECTIVECPP_CLAUSE42_UNDERSTAND_THE_TWO_MEANINGS_OF_TYPENAME_HPP
