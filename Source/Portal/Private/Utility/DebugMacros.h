#pragma once

#pragma region For_Inline_Macro 
#define __STRINGYFY__(x) FString(#x)
	
//https://learn.microsoft.com/ko-kr/cpp/preprocessor/predefined-macros?view=msvc-170
#if defined(__FILEW__)
 #define __SCOPE__ FString::Printf(TEXT("%s : %hs, (%d)"), *FPaths::GetCleanFilename(__FILEW__), __FUNCTION__, __LINE__)
#elif defined(__FILE__)
#define __SCOPE__ FString::Printf(TEXT("%s : %hs, (%d)"), *FPaths::GetCleanFilename(__FILE__), __FUNCTION__, __LINE__)
#else
#define __SCOPE__ FString::Printf(TEXT("%s : %hs, (%d)"), "Cant Find", __FUNCTION__, __LINE__)
#endif

#define __CLASS__(obj) (IsValid(obj) ? obj->StaticClass() : "")
#define __INSTANCE__(obj) (IsValid(obj) ? obj->GetName() : "")

#define __ORIGIN__ (IsValid(this) ? this->GetName() : __SCOPE__) + "::"
	

//https://learn.microsoft.com/ko-kr/cpp/preprocessor/variadic-macros?view=msvc-170
#define __GET_ARG1_MACRO__(_1, MACRO, ...) MACRO
#define __GET_ARGS2_MACRO__(_1, _2, MACRO, ...) MACRO
#define __GET_ARGS3_MACRO__(_1, _2, _3, MACRO, ...) MACRO
	
#define __PRINT_THIS_LINE__(Key) DEBUG_HELPER_VVV::PrintOnScreen(__SCOPE__, Key)
#define __PRINT_THIS_LINE_HASH__() DEBUG_HELPER_VVV::PrintOnScreen(__SCOPE__, 0, FColor::Green)

#define __PRINT_INSTANCE__(Instance, Key) DEBUG_HELPER_VVV::PrintOnScreen(__INSTANCE__(Instance), Key)
#define __PRINT_INSTANCE_HASH__(Instance) DEBUG_HELPER_VVV::PrintOnScreen(__INSTANCE__(Instance), 0, FColor::Orange)
#define __PRINT_THIS_INSTANCE_HASH__() DEBUG_HELPER_VVV::PrintOnScreen(__INSTANCE__(this), 0, FColor::Orange)

#define __PRINT_BOOL__(InBool, Key) DEBUG_HELPER_VVV::PrintBool(__STRINGYFY__(Key) + ":: " + __STRINGYFY__(InBool), InBool, Key)
#define __PRINT_BOOL_HASH__(InBool) DEBUG_HELPER_VVV::PrintBool(__ORIGIN__ + __STRINGYFY__(InBool), InBool, DEBUG_HELPER_VVV::Hashing(__STRINGYFY__(InBool)), FColor::Emerald)
#define __PRINT_INT__(InInt, Key) DEBUG_HELPER_VVV::PrintInt(__STRINGYFY__(Key) + ":: " + __STRINGYFY__(InInt), InInt, Key)
#define __PRINT_INT_HASH__(InInt) DEBUG_HELPER_VVV::PrintInt(__ORIGIN__ + __STRINGYFY__(InInt), InInt, DEBUG_HELPER_VVV::Hashing(__STRINGYFY__(InInt), __LINE__), FColor::Emerald)
#define __PRINT_FLOAT__(InFloat, Key) DEBUG_HELPER_VVV::PrintFloat(__STRINGYFY__(Key) + ":: " + __STRINGYFY__(InFloat), InFloat, Key)
#define __PRINT_FLOAT_HASH__(InFloat) DEBUG_HELPER_VVV::PrintFloat(__ORIGIN__ + __STRINGYFY__(InFloat), InFloat, DEBUG_HELPER_VVV::Hashing(__STRINGYFY__(InFloat), __LINE__), FColor::Emerald)
#define __PRINT_VECTOR__(InVec, Key) DEBUG_HELPER_VVV::PrintVector3(__STRINGYFY__(Key) + ":: " + __STRINGYFY__(InVec), InVec, Key)
#define __PRINT_VECTOR_HASH__(InVec) DEBUG_HELPER_VVV::PrintVector3(__ORIGIN__ + __STRINGYFY__(InVec), InVec, DEBUG_HELPER_VVV::Hashing(__STRINGYFY__(InVec), __LINE__), FColor::Emerald)
#define __PRINT_ROTATOR__(InRot, Key) DEBUG_HELPER_VVV::PrintRotator(__STRINGYFY__(Key) + ":: " + __STRINGYFY__(InRot), InRot, Key)
#define __PRINT_ROTATOR_HASH__(InRot) DEBUG_HELPER_VVV::PrintRotator(__ORIGIN__ + __STRINGYFY__(InRot), InRot, DEBUG_HELPER_VVV::Hashing(__STRINGYFY__(InRot), __LINE__), FColor::Emerald)
#define __PRINT_QUAT__(InQuat, Key) DEBUG_HELPER_VVV::PrintQuaternion(__STRINGYFY__(Key) + ":: " + __STRINGYFY__(InQuat), InQuat, Key)
#define __PRINT_QUAT_HASH__(InQuat) DEBUG_HELPER_VVV::PrintQuaternion(__ORIGIN__ + __STRINGYFY__(InQuat), InQuat, DEBUG_HELPER_VVV::Hashing(__STRINGYFY__(InQuat), __LINE__), FColor::Emerald)
	
#pragma endregion For_Inline_Macro

