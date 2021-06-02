//
// Created by Sea on 2021/6/1.
//

#ifndef ABSTRACTDATATYPE_LINEAR_TABLETEMPLATE_H
#define ABSTRACTDATATYPE_LINEAR_TABLETEMPLATE_H


//线性表模板类
template<class T>
class _List{
public:
    void _Clear();//置空线性表
    bool _IsEmpty();//线性表为空时，返回true
    bool _Append(const T value);//在表尾添加一个元素value，表长度增加1
    virtual bool _Insert(const int pos,const T value){return true;};//在位置pos上插入一个元素，表长度增加1
    virtual bool _Delete(const int p){return true;};//删除位置p上的元素 表长度减1

    bool _GetPos(int &p,T &value);//查找值为value元素并返回其位置
    bool _GetValue(const int p,T &value);//把位置p元素值返回到变量value
    bool _setValue(const int p,const T value);//把value修改位置p的元素值
};

#endif //ABSTRACTDATATYPE_LINEAR_TABLETEMPLATE_H
