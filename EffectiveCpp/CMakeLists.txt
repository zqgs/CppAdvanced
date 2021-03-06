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
        Clause09_Never_Call_Virtual_During_Construct_Or_Cestruct.hpp "Clause10_Have_Operators_Return_Ref_To_p(this).hpp" Clause11_Handle_Assign_To_Self_In_Operator.hpp Clause12_Copy_All_Parts_Of_An_Object.hpp Clause13_Use_Object_To_Manage_Resources.hpp Clause14_Carefully_About_Copying_In_Manag_Class.hpp Clause15_Provide_Access_To_Raw_Res_In_RAIIClasses.hpp Clause16_Same_From_Of_New_And_Delete.hpp Clause17_Newed_Object_In_Smart_Pointers.hpp Clause18_Make_Interfaces_To_Use_Right.hpp Clause19_Treat_Class_Design_As_Type_Design.hpp Clause20_Prefer_Pass-By-Ref_Const_To_Pass-By-Value.hpp Clause21_Don't_Try_Return_a_ReF_When_Must_Return_Obj.hpp Clause22_Declare_Data_Members_Private.hpp Clause23_Prefer_non-Member_Or_non-Friend_To_MemberFunciton.hpp "Clause24_If all parameters need to be converted, please use the non-member function.hpp" Clause25_Consider_Support_for_A_Non_Throwing_Swap.hpp "Clause26_Delay the appearance of the variable definition formula as long as possible.hpp" Clause27_Minimize_Casting.hpp Clause28_Avoid_Return_Handles_to_Object_internals.hpp Clause29_Strice_For_Exception-safe_Code.hpp Clause30_Understand_the_ins_and_Outs_of_Inlining.hpp Clause31_Minimize_Compilation_Dependencies_Between_File.hpp Clause32_Make_Sure_public_inheritance_models_isA.hpp Clause33_Avoid_hiding_inherited_Name.hpp "Clause34_Distinguishing between interface inheritance and implementation inheritance.hpp" Clause35_Consider_Alternatives_to_virtual_function.hpp Clause36_Never_ReDefine_InHerited_non-virtual_Func.hpp Clause37_Never_Redefine_fun_inherited_default_Param_value.hpp Clause38_Model_has-a_is_Implemented-in-terms-of_through_composition.hpp Clause39_Use_Private_inheritance_Judiciously.hpp Clause40_Use_Multiple_Inheritance_Judiciously.hpp Clause41_Understand_implicit_Interface_And_Compile-Time_Polymorphism.hpp Clause42_Understand_The_Two_Meanings_Of_Typename.hpp Clause43_Lerning_access_Name_In_templatized_base_class.hpp Clause44_Fator_Param-independent_code_out_of_template.hpp Clause45_Use_Member_Fun_template_to_Accept_all-compatible-types.hpp Clause46_Define_non-member-function_inside_templates_when_type_conversion_are_desired.hpp)