cmake_minimum_required(VERSION 3.17.3)
project(AbstractDataType)

set(CMAKE_CXX_STANDARD 14)

add_executable(AbstractDataType main.cpp
        Algorithm_Introduction.hpp
        Abstract_Data_Type.hpp
        List_DoubleLinked.hpp
        List_Sequence.hpp
        List_SinglyLinked.hpp
        Stack_Array_Based.hpp
        Stack_Link_Based.hpp)
