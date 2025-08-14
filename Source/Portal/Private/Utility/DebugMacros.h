#pragma once

#pragma region For_Inline_Macro 
#define __STRINGYFY__(x) FString(#x)
	
//https://learn.microsoft.com/ko-kr/cpp/preprocessor/predefined-macros?view=msvc-170
#if defined(__FILEW__)
	#define __SCOPE__ FString::Printf(TEXT("%s : %hs, (%d)"), *FPaths::GetCleanFilename(__FILEW__), __FUNCTION__, __LINE__)
#elif defined(__FILE__)
	#define __SCOPE__ FString::Printf(TEXT("%s : %hs, (%d)"), *FPaths::GetCleanFilename(__FILE__), __FUNCTION__, __LINE__)
#else
	#define __SCOPE__ FString::Printf(TEXT("%s : %hs, (%d)"), *FPaths::Get, __FUNCTION__, __LINE__)
#endif

#define __CLASS__(obj) (IsValid(obj) ? obj->StaticClass() : "")
#define __INSTANCE__(obj) (IsValid(obj) ? obj->GetName() : "")

#define __ORIGIN__ (IsValid(this) ? this->GetName() : __FUNCTION__) + "::"

//https://learn.microsoft.com/ko-kr/cpp/preprocessor/variadic-macros?view=msvc-170
#define __WRAP__(expression)							expression
#define __PREFIX__(...)									0, ##__VA_ARGS__
#define __ARGS__(_1, _2, _3, _4, expression, ...)		expression

#define __GET_ARGS_COUNT_IMPL__(...)					__WRAP__(__ARGS__(__VA_ARGS__, 3, 2, 1, 0))
#define __GET_ARGS_COUNT__(...)							__GET_ARGS_COUNT_IMPL__(__PREFIX__(__VA_ARGS__))

#define __MAKE_EXPRESSION__(expression, counting)		expression##counting
#define __MAKE_ARGS_MACRO__(expression, counting)		__MAKE_EXPRESSION__(expression, counting)

#define __PRINT_THIS_LINE__1(Key) FDebugHelperVVV::Get()->PrintOnScreen(__SCOPE__, __SCOPE__, Key)
#define __PRINT_THIS_LINE__0() FDebugHelperVVV::Get()->PrintOnScreen(__SCOPE__, __SCOPE__,\
	FDebugHelperVVV::Get()->Hashing(__SCOPE__, __LINE__), FColor::Green)

#define __PRINT_INSTANCE__2(Instance, Key) FDebugHelperVVV::Get()->PrintOnScreen(__SCOPE__, __INSTANCE__(Instance), Key)
#define __PRINT_INSTANCE__1(Instance) FDebugHelperVVV::Get()->PrintOnScreen(__SCOPE__, __INSTANCE__(Instance),\
	FDebugHelperVVV::Get()->Hashing(__INSTANCE__(Instance), __LINE__), FColor::Orange)
#define __PRINT_INSTANCE__0() FDebugHelperVVV::Get()->PrintOnScreen(__SCOPE__, __INSTANCE__(this),\
	FDebugHelperVVV::Get()->Hashing(__INSTANCE__(this), __LINE__), FColor::Orange)

#define __PRINT_SCREEN__2(InStr, Key) FDebugHelperVVV::Get()->PrintOnScreen(__SCOPE__, __STRINGYFY__(Key) + " : " + InStr, Key)
#define __PRINT_SCREEN__1(InStr) FDebugHelperVVV::Get()->PrintOnScreen(__SCOPE__, InStr,\
	FDebugHelperVVV::Get()->Hashing(__STRINGYFY__(InStr), __LINE__), FColor::Emerald)
#define __PRINT_BOOL__2(InBool, Key) FDebugHelperVVV::Get()->PrintBool(__SCOPE__, __STRINGYFY__(Key) + " : " + __STRINGYFY__(InBool), InBool, Key)
#define __PRINT_BOOL__1(InBool) FDebugHelperVVV::Get()->PrintBool(__SCOPE__, __ORIGIN__ + __STRINGYFY__(InBool), InBool,\
 	FDebugHelperVVV::Get()->Hashing(__STRINGYFY__(InBool), __LINE__), FColor::Emerald)
#define __PRINT_BYTE__2(InByte, Key) FDebugHelperVVV::Get()->PrintByte(__SCOPE__, __STRINGYFY__(Key) + " : " + __STRINGYFY__(InByte), InByte, Key)
#define __PRINT_BYTE__1(InByte) FDebugHelperVVV::Get()->PrintByte(__SCOPE__, __STRINGYFY__(InByte), InByte,\
	FDebugHelperVVV::Get()->Hashing(__STRINGYFY__(InByte), __LINE__), FColor::Emerald)
#define __PRINT_INT__2(InInt, Key) FDebugHelperVVV::Get()->PrintInt(__SCOPE__, __STRINGYFY__(Key) + " : " + __STRINGYFY__(InInt), InInt, Key)
#define __PRINT_INT__1(InInt) FDebugHelperVVV::Get()->PrintInt(__SCOPE__, __ORIGIN__ + __STRINGYFY__(InInt), InInt,\
	FDebugHelperVVV::Get()->Hashing(__STRINGYFY__(InInt), __LINE__), FColor::Emerald)
#define __PRINT_FLOAT__2(InFloat, Key) FDebugHelperVVV::Get()->PrintFloat(__SCOPE__, __STRINGYFY__(Key) + " : " + __STRINGYFY__(InFloat), InFloat, Key)
#define __PRINT_FLOAT__1(InFloat) FDebugHelperVVV::Get()->PrintFloat(__SCOPE__, __ORIGIN__ + __STRINGYFY__(InFloat), InFloat,\
 	FDebugHelperVVV::Get()->Hashing(__STRINGYFY__(InFloat), __LINE__), FColor::Emerald)
#define __PRINT_VECTOR__2(InVec, Key) FDebugHelperVVV::Get()->PrintVector3(__SCOPE__, __STRINGYFY__(Key) + " : " + __STRINGYFY__(InVec), InVec, Key)
#define __PRINT_VECTOR__1(InVec) FDebugHelperVVV::Get()->PrintVector3(__SCOPE__, __ORIGIN__ + __STRINGYFY__(InVec), InVec,\
 	FDebugHelperVVV::Get()->Hashing(__STRINGYFY__(InVec), __LINE__), FColor::Emerald)
#define __PRINT_ROTATOR__2(InRot, Key) FDebugHelperVVV::Get()->PrintRotator(__SCOPE__, __STRINGYFY__(Key) + " : " + __STRINGYFY__(InRot), InRot, Key)
#define __PRINT_ROTATOR__1(InRot) FDebugHelperVVV::Get()->PrintRotator(__SCOPE__, __ORIGIN__ + __STRINGYFY__(InRot), InRot,\
 	FDebugHelperVVV::Get()->Hashing(__STRINGYFY__(InRot), __LINE__), FColor::Emerald)
#define __PRINT_QUAT__2(InQuat, Key) FDebugHelperVVV::Get()->PrintQuaternion(__SCOPE__, __STRINGYFY__(Key) + " : " + __STRINGYFY__(InQuat), InQuat, Key)
#define __PRINT_QUAT__1(InQuat) FDebugHelperVVV::Get()->PrintQuaternion(__SCOPE__, __ORIGIN__ + __STRINGYFY__(InQuat), InQuat,\
 	FDebugHelperVVV::Get()->Hashing(__STRINGYFY__(InQuat), __LINE__), FColor::Emerald)
	
#pragma endregion For_Inline_Macro

