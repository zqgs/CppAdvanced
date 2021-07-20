cmake_minimum_required(VERSION 3.17)
project(EffectiveCpp)

set(CMAKE_CXX_STANDARD 14)

add_executable(EffectiveCpp
        main.cpp
        Clause01_ViewCpp_As_a_Feaderation_of_Languages.hpp
        Clause02_Prefer_consts_enums_inline_to_define.hpp
        Clause03_Use_Const_Whenever_possible.hpp
        Clause04_Before_Used_Object_MaksSure_Is_Initialized.hpp
        Clause05_Know_Functions_C++_Silently_Writes_And_Calls.hpp
        Clause06_Don't_Use_Function_of_Explicitly_Disallow.hpp
        Clause08_Prevent_Exception_Leave_Destructors.hpp
        Clause09_Never_Call_Virtual_During_Construct_Or_Cestruct.hpp "Clause10_Have_Operators_Return_Ref_To_p(this).hpp" Clause11_Handle_Assign_To_Self_In_Operator.hpp Clause12_Copy_All_Parts_Of_An_Object.hpp Clause13_Use_Object_To_Manage_Resources.hpp Clause14_Carefully_About_Copying_In_Manag_Class.hpp Clause15_Provide_Access_To_Raw_Res_In_RAIIClasses.hpp Clause16_Same_From_Of_New_And_Delete.hpp Clause17_Newed_Object_In_Smart_Pointers.hpp Clause18_Make_Interfaces_To_Use_Right.hpp)