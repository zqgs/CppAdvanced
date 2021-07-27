//
// Created by Sea on 2021/7/22.
//

#ifndef EFFECTIVECPP_CLAUSE23_PREFER_NON_MEMBER_OR_NON_FRIEND_TO_MEMBERFUNCITON_HPP
#define EFFECTIVECPP_CLAUSE23_PREFER_NON_MEMBER_OR_NON_FRIEND_TO_MEMBERFUNCITON_HPP

//条款23:宁以non-member、non-friend替换member函数

//例1:
class WebBrowser{
public:
    void clearCache(){}
    void clearHistory(){}
    void removeCookies(){}
    //如果想同时执行一些动作，可能会提供一个这样的函数
    void clearEverything(){
        clearCache();
        clearHistory();
        removeCookies();
    }
};

//也有可能是一个非成员函数
void clearBrowserexp1(WebBrowser &wb){
    wb.clearCache();
    wb.clearHistory();
    wb.removeCookies();
}

//思考:上面clear的哪种实现更好？
//从封装的角度思考:越少的代码可以访问它，表明越多的数据可被封装，而我们就越能自由的改变对象数据。

/*  为什么non-member non-friend函数要比class member更具封装性？
 *第一:class-member/friend函数能够直接访问类内的所有资源(private以及enums、typedefs等等也不例外)
 *第二:non-member/non-friend并不能直接访问类内的私有化资源，但是也可以实现成员函数所实现的机能。
 *所以non-member/non-friend更具封装性
 */


/* 关于为什么non-member/non-friend为什么要比class member更具封装性。需要注意两点:
 * 第一:这种论述只适用于non-member/non-friend函数，friend函数对private成员访问权力与member函数相同。
 *因此两者的对封装的力度相同。
 * 第二:只因在意封装性而让函数"成为类的non-member",并不意味它"不可以是另一个类的member"。可以令non-member
 *成为static member函数，只要不是class一部分或成为其friend，就不会影响class的封装性。
 */

//以上思考与讨论在C++中的实现:
namespace WebBrowserStuff{
    class  WebBrowserExp2{};
    void clearBrowser(WebBrowserExp2 &wb){}
}
//当一个类拥有大量的便利函数，分别代表不通用途。我们可以模仿C++标准库来实现类似的效果
//头文件1:#include "WebBrowserExp3.h" 表示核心机能
namespace WebBrowserStuff{
    class  WebBrowserExp3{};
    void clearBrowser(WebBrowserExp3 &wb){}
}
//头文件2:#include ""WebBrowserfun1.h"" 表示功能1
namespace WebBrowserStuff{
    void BrowserFun1(WebBrowserExp3 &wb){}
}
//头文件3:#include ""WebBrowserfun2.h"" 表示功能2
namespace WebBrowserStuff{
    void BrowserFun2(WebBrowserExp3 &wb){}
}

//以上实现方式正是C++标准库的组织方式。当用户想使用某些机能时，可以仅声明部分头文件，这样最大程度的降低了编译相依。
//此种方式并不适用于切割class的成员函数，因为class必须整体定义，不能被切割为片段。


//将多个便利函数放在多个头文件内，但隶属同一个命名空间，意味着可以轻松扩展这一便利函数。
//只需要将更多的non-member/non-friend函数添加进此命名空间内，并建立相应的头文件即可。

//namespace相比class，class定义式相对客户而言时不能扩展的(扩展方式只能通过派生，但派生类无法访问基类的private)。

/*重点记住:
 * 1.宁可拿non-member、non-friend替换member函数。这样做可以增加封装性、包裹弹性和机能扩充性。
 */

#endif //EFFECTIVECPP_CLAUSE23_PREFER_NON_MEMBER_OR_NON_FRIEND_TO_MEMBERFUNCITON_HPP
