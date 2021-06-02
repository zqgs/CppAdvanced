#include <iostream>
#include <chrono>
#include "Algorithm_Introduction.hpp"
#include "Sequence_Table.hpp"



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
    return 0;
}
