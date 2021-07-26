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
//条款22：成员变量应该是private。如果不是，那么就有无限量的函数可以访问它。

/*  为什么non-member non-friend函数要比class member更具封装性？
 *第一:class-member/friend函数能够直接访问类内的所有资源(private以及enums、typedefs等等也不例外)
 *第二:non-member/non-friend并不能直接访问类内的私有化资源，但是也可以实现成员函数所实现的机能。
 *所以non-member/non-friend更具封装性
 */


#endif //EFFECTIVECPP_CLAUSE23_PREFER_NON_MEMBER_OR_NON_FRIEND_TO_MEMBERFUNCITON_HPP
