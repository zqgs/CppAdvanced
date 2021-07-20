//
// Created by Sea on 2021/7/20.
//

#ifndef EFFECTIVECPP_CLAUSE_TREAT_CLASS_DESIGN_AS_TYPE_DESIGN_HPP
#define EFFECTIVECPP_CLAUSE_TREAT_CLASS_DESIGN_AS_TYPE_DESIGN_HPP


//条款19:设计class犹如设计type
//一个类或类型的设计:重载函数、操作符的分配和归还、定义对象的初始化和终结等等。
//设计一个类时应该努力向着C++语言设计者当初设计语言内置类型时靠拢。


//如何高效设计高效的classes，必须了解一下问题:
//1.新class(type)的对象应该如果被创建和销毁？
//2.对象的初始化和对象的赋值应该有什么样的差别？
//3.新class(type)的如果被passed by value(值传递)，意味着什么？
//4.什么是新class(type)的"合法值"？
//5.新class(type)的需要配合某个继承体系吗？
//6.新class(type)需要什么样的转换？
//7.什么样的操作符和函数对此新class(type)而言是合理的？
//8.什么样的标准函数应该驳回？
//9.谁该取用新class(type)的的成员？
//10.什么是新class(type)的的"未声明接口"？
//11.新class(type)有多么一般化？
//12.设计前考虑真的需要一个新class(type)吗？



#endif //EFFECTIVECPP_CLAUSE_TREAT_CLASS_DESIGN_AS_TYPE_DESIGN_HPP
