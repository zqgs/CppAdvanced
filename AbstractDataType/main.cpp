#include <iostream>
#include <chrono>
#include "Algorithm_Introduction.hpp"
#include "List_Sequence.hpp"
//#include "SinglyLinked_List.hpp"
#include "List_DoubleLinked.hpp"
#include "Stack_Array_Based.hpp"
#include "Stack_Link_Based.hpp"

int main() {
    /*
    std::vector<Item<int>> iVec={0,1,3,5,7,9};
    std::chrono::high_resolution_clock::time_point beginTime =  std::chrono::high_resolution_clock::now();
    SeqSerch(iVec,iVec.size(),8);//穷举法
    std::chrono::high_resolution_clock::time_point endTime =  std::chrono::high_resolution_clock::now();
    std::chrono::milliseconds timeInterval = std::chrono::duration_cast< std::chrono::milliseconds>(endTime - beginTime);
    std::cout << "SeqSerch:" << timeInterval.count() << "ms\n";

    beginTime =  std::chrono::high_resolution_clock::now();
    BinSerch(iVec,iVec.size(),8);//二分法
    endTime =  std::chrono::high_resolution_clock::now();
    timeInterval = std::chrono::duration_cast< std::chrono::milliseconds>(endTime - beginTime);
    std::cout << "BinSerch:" << timeInterval.count() << "ms\n";

    beginTime =  std::chrono::high_resolution_clock::now();
    Design(iVec,iVec.size(),2);

    endTime =  std::chrono::high_resolution_clock::now();
    timeInterval = std::chrono::duration_cast< std::chrono::milliseconds>(endTime - beginTime);
    std::cout << "Design:" << timeInterval.count() << "ms\n";

    for (int i = 0; i < iVec.size(); ++i)
        std::cout<<iVec[i].getKey()<<" ";
    std::cout<<"\n";

    //std::cout << "BinSerch:"<< BinSerch(iVec,iVec.size(),9) << std::endl;

    std::clog<< "BinSerch:"<< BinSerch(iVec,iVec.size(),9) << std::endl;
     */

    /*
    arrList<int> a(10);
    a._Insert(0,5);
    a._Insert(1,2);

    for(int i=0;i<10;i++)
        std::cout<<a[i]<<" ";
    std::cout<<"\n";


    a._Delete(0);
    for(int i=0;i<10;i++)
        std::cout<<a[i]<<" ";
    std::cout<<"\n";
     */

    /*
    linkList<int> *_list = new linkList<int>(3);
    _list->_Insert(1,5);
    _list->_Insert(2,2);
    int a;
    _list->_GetValue(1,a);
    std::cout<<a<<std::endl;
    _list->_GetValue(2,a);
    std::cout<<a<<std::endl;
     delete _list;
     */

    /*
    std::cout<<"-----ADDbegin-----\n";
    DoubleLinkList<int> *DList = new DoubleLinkList<int>();
    DList->_Insert(1,3);
    DList->_Insert(2,4);
    DList->_Insert(3,5);
    DList->_Insert(4,6);
    int b;
    DList->_GetValue(3,b);
    std::cout<<b<<std::endl;
    std::cout<<"-----ADDend-----\n";

    std::cout<<"-----Deletebegin-----\n";
    DList->_Delete(1);
    DList->_Delete(2);
    DList->_Delete(3);
    DList->_Delete(4);

    int c=0;
    DList->_GetValue(1,c);
    std::cout<<c<<std::endl;
    std::cout<<"-----Deleteend-----\n";
     */
    /*
    Array_Stack<int> *as = new Array_Stack<int>(5);
    as->push(7);
    int d=0;
    as->pop(d);
    std::cout<<d<<std::endl;

    delete as;
     */
    /*
    lnkStack<int> *st = new lnkStack<int>() ;
    st->push(1);
    st->push(2);
    st->push(3);
    int e;
    st->pop(e);
    std::cout<<e<<std::endl;
    st->pop(e);
    std::cout<<e<<std::endl;
    st->pop(e);
    std::cout<<e<<std::endl;
    st->pop(e);
    std::cout<<e<<std::endl;
     */
    return 0;
}
