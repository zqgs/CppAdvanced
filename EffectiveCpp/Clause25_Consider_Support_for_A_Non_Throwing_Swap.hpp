//
// Created by Sea on 2021/7/28.
//

#ifndef EFFECTIVECPP_CLAUSE25_CONSIDER_SUPPORT_FOR_A_NON_THROWING_SWAP_HPP
#define EFFECTIVECPP_CLAUSE25_CONSIDER_SUPPORT_FOR_A_NON_THROWING_SWAP_HPP
#include <vector>
#include <iostream>
//条款25:考虑写出一个不抛出异常的swap函数

//先来看一下标准库的swap实现
/*namespace Cl25___std{//假装是标准库
    template <typename T>
    //只要类型支持copying(通过拷贝构造函数和拷贝赋值操作符完成)
    void swap(T& a,T& b){
        T temp(a); //a复制到temp
        a = b;//b复制到a
        b = temp;//temp复制到b
    }
}*/
//对某些类型而言:以指针指向一个对象，内含真正的数据。这种设计常见的表现形式为pimpl手法
class Cl25_WidgetImpl{
private:
    int a,b,c;
    std::vector<double> v;
};
class Cl25_Widget{
public:
    Cl25_Widget(const Cl25_Widget& rhs){}
    Cl25_Widget& operator=(const Cl25_Widget& rhs){

        //复制成员
        *pImpl = *(rhs.pImpl);
        return *this;
    }

private:
    Cl25_WidgetImpl* pImpl;
};
//如果要交换两个Cl25_Widget的值，唯一需要做的是交换pImpl指针，但是缺省swap却不知道。此时使用缺省swap那么其内部发生了什么？
//swap会复制三个Cl25_Widget，还会复制三个Cl25_WidgetImpl对象，此时效率会比较低下。

//强制特化std::swap会发生什么？
//错误示例1:通常我们不允许改变std命名空间中的任何东西，但可以为标准template制造特化版本，使它专属为某个类服务
namespace std{
    template<>//表示std::swap的一个全特化版本。
    void swap<Cl25_Widget>(Cl25_Widget& a,Cl25_Widget& b){
        //std::swap(a.pImpl,b.pImpl); //访问了私有成员，编译器直接报错
    }
}
//错误示例2：示例1创建特化版本失败后,如果在class内部创建swap函数又会怎样？
class Cl25_WidgetExp1{
public:
    Cl25_WidgetExp1(const Cl25_WidgetExp1& rhs){}
    Cl25_WidgetExp1& operator=(const Cl25_WidgetExp1& rhs){
        //复制成员
        *pImpl = *(rhs.pImpl);
        return *this;
    }
    void swap(Cl25_WidgetExp1& other){
        std::swap(pImpl,other.pImpl);
    }
private:
    Cl25_WidgetImpl* pImpl;
};
//再次为Cl25_WidgetExp1创建特化版本
namespace std{
    template<>
    void swap<Cl25_WidgetExp1>(Cl25_WidgetExp1& a,Cl25_WidgetExp1& b){
        a.swap(b); //终于可以通过编译，还与STL有一致性，因为所有STL都提供了public swap成员函数和std::swap特化版本
    }
}

//错误示例3:在示例2的基础上再深入一点，如果Cl25_WidgetExp1和Cl25_WidgetImpl都是class template而非calsses,实现std特化swap又是怎样的呢？
template <typename T>
class Cl25_WidgetImplExp1{
private:
    T a,b,c;
    std::vector<double> v;
};

template <typename T>
class Cl25_WidgetExp2{
public:
    Cl25_WidgetExp2(const Cl25_WidgetExp2& rhs){}
    Cl25_WidgetExp2& operator=(const Cl25_WidgetExp2& rhs){
        //复制成员
        *pImpl = *(rhs.pImpl);
        return *this;
    }
    void swap(Cl25_WidgetExp2& other){
        std::swap(pImpl,other.pImpl);
    }
private:
    Cl25_WidgetImplExp1<T>* pImpl;
};

//为Cl25_WidgetExp2创造std特化版本，开始交换两个Cl25_WidgetExp2的数据
/*namespace std{
    template<typename T>
    //发现编译不通过，C++只允许对class template偏特化，不允许对function template偏特化
    void swap<Cl25_WidgetExp2<T>>(Cl25_WidgetExp2<T>& a,Cl25_WidgetExp2<T>& b){
        a.swap(b);
    }
}*/

//既然偏特化不通过，那么采取重载function template的方式呢？其实针对std的function template重载都是不行的
/*namespace std{
    template <typename T>
    //看似可行，其实不然。C++委员会禁止我们膨胀标准库中已经声明好的东西。
    void swap(Cl25_WidgetExp2<T>& a,Cl25_WidgetExp2<T>& b){
        a.swap(b);
    }
}*/

//正确示例4:一般而言，重载function template是可行的，针对std标准库除外。
namespace WidgetStuff{
    template<typename T>
    class Cl25_WidgetExp3{
    public:
        Cl25_WidgetExp3(const Cl25_WidgetExp3& rhs){}
        Cl25_WidgetExp3& operator=(const Cl25_WidgetExp3& rhs){
            //复制成员
            *pImpl = *(rhs.pImpl);
            return *this;
        }
        void swap(Cl25_WidgetExp3& other){
            std::swap(pImpl,other.pImpl);
        }
    private:
        Cl25_WidgetImplExp1<T>* pImpl;
    };

    //成功,让调用者调用swap能够取得较高效的版本
    template<typename T>
    void swap(Cl25_WidgetExp3<T>& a,Cl25_WidgetExp3<T>& b){
        a.swap(b);
    }

    //示例4中的做法对classes和class template均可。
}


//实例5:从调用者的角度出发，他们需要的是如果swap存在高效特化版本，则调用之。不存在则调用std::swap
template <typename T>
void doSomeThing(T& obj1,T& obj2)
{
    //1.正确使用
    using std::swap;
    swap(obj1,obj2);

    //2.错误使用(并不能说错误，只是当T存在高效版本时，并不能正确调用之)
    std::swap(obj1,obj2);

    //思考为什么2是错误的？
    //答:因为2强制让编译器选择了std的方法，所以是不行的。由于1中使用了using将std::swap暴露出来，编译
    //器根据"实参取决的查找规则"会优先查找T的高效swap版本，如果找不到就会调用using暴露的std::swap标准版本，
    //如果想让编译器按照我们的设想调用对应的swap函数，那么采用using将会是不错的选择。
}

//针对default swap、member swap、non-member swap、std::swap特化版本、以及对swap的调用总结:
/* 首先，如果swap缺省码对class或class template提供可以接收的效率，那么就无需添加额外的swap版本，
 *调用者将自动获得缺省swap版本。
 * 其次，如果swap缺省版本的效率不足(可能在class或class template中使用了某种pimpl手法)，那么我们应该尝试做一下事情:
 *1.提供一个public swap函数，让它高效的完成两个对象值的置换，这个函数不应抛出异常。
 *2.在class或template所在的命名空间(非std)提供一个non-member swap,并令他调用1的swap成员函数
 *3.如果正在编写class(而非class template)，可以为class创建一个std::swap特化版本，并令它调用1的swap成员函数
 * 最后，如果调用swap,确定包含一个using声明式，以便让std::swap在函数内曝光，无需加namespace修饰符('std::')，直接调用swap即可
 * 终:swap绝不抛出异常这一约束只施行与member，不可以实施于non-member。原因:swap缺省版本是以拷贝构造函数和拷贝复制操作符为基础，
 *一般情况下两者都允许抛出异常。
 */


/*重点记住:
 * 1.当std::swap对类型效率不高时，提供一个swap成员函数，并不抛出异常。
 * 2.如果提供一个member swap，也该提供一个non-member swap用来调用前者，对于classes(非class template)，请特化std::swap
 * 3.调用swap时应针对std::swap使用using声明式，然后调用swap并且不带任何命名空间的修饰
 * 4.为"用户定义类型"进行std template全特化是好的，但千万不要尝试在std内加入对std而言全新的东西
 */

#endif //EFFECTIVECPP_CLAUSE25_CONSIDER_SUPPORT_FOR_A_NON_THROWING_SWAP_HPP
