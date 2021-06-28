//
// Created by Sea on 2021/6/16.
//

#ifndef ABSTRACTDATATYPE_TREE_BINARY_EXPRESSION_HPP
#define ABSTRACTDATATYPE_TREE_BINARY_EXPRESSION_HPP


/*
 二叉表达式树
 中序遍历(左叶、节点、右叶)
    通过递归产生一个带括号的左表达式，然后打印出在根处的操作符，最后再递归地产生一个带括号
    的右表达式从而得到一个对括号整体进行运算的中缀表达式。
    中序产生的表达式：(a+b*c)+((d*e+f)*g)

 后序遍历(左叶、右叶、节点)
    递归的打印出左子树、右子树，然后打印操作符。依次入栈，遇到符号则弹出计算
    后序产生的表达式：a b c * + d e * f + g *

 前序遍历(节点、左叶、右叶)
    先打印操作符，然后再打印出左子树和右子树
    前序产生的表达式：+ + a * b c * + * d e f g
*/

#endif //ABSTRACTDATATYPE_TREE_BINARY_EXPRESSION_HPP
