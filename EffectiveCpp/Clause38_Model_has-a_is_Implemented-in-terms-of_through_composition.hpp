//
// Created by Sea on 2021/9/10.
//

#ifndef EFFECTIVECPP_CLAUSE38_MODEL_HAS_A_IS_IMPLEMENTED_IN_TERMS_OF_THROUGH_COMPOSITION_HPP
#define EFFECTIVECPP_CLAUSE38_MODEL_HAS_A_IS_IMPLEMENTED_IN_TERMS_OF_THROUGH_COMPOSITION_HPP

#include <iostream>
#include <string>
#include <list>
#include <algorithm>

//条款38:通过符合塑模出has-a或"根据某物实现出"

//复合(composition)式类型之间的一种关系,当某种类型的对象内含它种类型的对象，便是复合。
//例子1:复合
class Cl38_Address {/*...*/};
class Cl38_PhoneNumber {/*...*/};
class Cl38_Person{
private:
    std::string name;//合成成分1
    Cl38_Address address;//合成成分2
    Cl38_PhoneNumber voiceNumber;//合成成分3
    Cl38_PhoneNumber faxNumber;//合成成分4
};
//程序的世界中复合的同义词:分层（layering）、内含（containment）、聚合（aggregation）、内嵌（embedding）
//"public继承"是is-a,复合意味着has-a(有一个/根据某物实现出)
//软件领域分类:汽车、人、一张张视频画面属于应用域。细节实现:缓冲区、互斥器、查找树属于实现域。
//当复合发生于应用域时，表现出has-a关系。当复合发生于实现域时，表现出根据某物实现出特性。


//实现一个Set容器。Set跟list很像,却不可以使用is-a概念。
template <class T>
class Cl38_Sets: public  std::list<T>{};//为什么不可以使用is-a概念呢？答:is-a表示派生类为真的事对于基类也一定为真，但Set不允许出现相同元素,但list却可以。

//用has-a实现一个Set容器(并非红黑树,此set不注重效率)。Set跟list很像,大部分机能可以依赖list来实现
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
/*重点记住:
 *  1.复合(composition)的意义和public继承完全不同。
 *  2.在应用域(application domain),复合意味着has-a(有一个。例子:人有住址等)。在实现域，复合意味着根据某物实现出。
 */

#endif //EFFECTIVECPP_CLAUSE38_MODEL_HAS_A_IS_IMPLEMENTED_IN_TERMS_OF_THROUGH_COMPOSITION_HPP
