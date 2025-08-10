#pragma once

#include "CoreMinimal.h"
#include "DebugMacros.h"

DECLARE_LOG_CATEGORY_EXTERN(CustomDebuggingLog, Type::Log, All);

/*
*	Useful Macro. You can Copy And Paste these with Double-Click
*	Writing "debughelper" Makes Auto Word Completions

* 1. Log
DEBUG_HELPER_LOG_THIS_LINE
DEBUG_HELPER_WARNING_THIS_LINE
DEBUG_HELPER_LOG_THIS_INSTANCE(this)


* 2. Print On Screen
* () : Can Use Without (Argument)
* This : Send To Argument "this" in your class
* In : Send To Argument "your value" in your class
* Key : If equal key is inserted, one Message Cover the other. if empty, Use SelfHashing

DEBUG_HELPER_PRINT_LINE((Key))						// if empty args, Print "current line"
DEBUG_HELPER_PRINT_INSTANCE((instance||this, Key))	// if empty args, Print "current this"

DEBUG_HELPER_PRINT_BOOL(InBool, (Key))
DEBUG_HELPER_PRINT_INT(InInt, (Key))
DEBUG_HELPER_PRINT_FLOAT(InFloat, (Key))
DEBUG_HELPER_PRINT_VECTOR(InVec, (Key))
DEBUG_HELPER_PRINT_ROTATOR(InRot, (Key))
DEBUG_HELPER_PRINT_QUAT(InQuat, (Key))

*/
namespace DEBUG_HELPER_VVV
{
#pragma region Log_Message

#define DEBUG_HELPER_LOG_THIS_LINE \
	UE_LOG(CustomDebuggingLog, Type::Log, TEXT("%s"), *(__SCOPE__))
#define DEBUG_HELPER_WARNING_THIS_LINE \
	UE_LOG(CustomDebuggingLog, Type::Warning, TEXT("%s"), *(__SCOPE__))
#define DEBUG_HELPER_LOG_INSTANCE(Instance) \
	UE_LOG(CustomDebuggingLog, Type::Log, TEXT("%s, %s"), *(__INSTANCE__(Instance)))
#define DEBUG_HELPER_LOG_THIS_INSTANCE \
	UE_LOG(CustomDebuggingLog, Type::Log, TEXT("%s, %s"), *(__INSTANCE__(this)))
	
	// Custom Message
	void Log(const FString& Msg);	
	void Warning(const FString& Msg);
	void Error(const FString& Msg);
	void CheckBool(const FString& StrName, const bool& InBool);
	void CheckInt(const FString& StrName, const int& InInt);
	void CheckEnum(const FString& StrName, const uint8& InByte);
	void CheckBytesFour(const FString& StrName, const uint32& InBytes);
	void CheckPtr(const FString& StrName, const void* InPtr);
	void CheckFloat(const FString& StrName, const float& InFloat, uint32 Decimal = 4);
	void CheckVector3(const FString& StrName, const FVector& InVector3, uint32 Decimal = 4);
	void CheckRotator(const FString& StrName, const FRotator& InRotator, uint32 Decimal = 4);
	void CheckQuaternion(const FString& StrName, const FQuat& InQuaternion, uint32 Decimal = 4);
	
#pragma endregion Log_Message
	
#pragma region Screen_Message
	// if empty, Print "current line"
#define DEBUG_HELPER_PRINT_LINE(...) __GET_ARGS2_MACRO__(dummy, ##__VA_ARGS__, __PRINT_THIS_LINE__, __PRINT_THIS_LINE_HASH__)(__VA_ARGS__)
	// if empty, Print "current this instance"
#define DEBUG_HELPER_PRINT_INSTANCE(...) __GET_ARGS3_MACRO__(dummy, ##__VA_ARGS__, __PRINT_INSTANCE__, __PRINT_INSTANCE_HASH__, __PRINT_THIS_INSTANCE_HASH__)(__VA_ARGS__)

#define DEBUG_HELPER_PRINT_BOOL(...) __GET_ARGS2_MACRO__(__VA_ARGS__, __PRINT_BOOL__, __PRINT_BOOL_HASH__) (__VA_ARGS__)
#define DEBUG_HELPER_PRINT_INT(...) __GET_ARGS2_MACRO__(__VA_ARGS__, __PRINT_INT__, __PRINT_INT_HASH__)(__VA_ARGS__) 
#define DEBUG_HELPER_PRINT_FLOAT(...) __GET_ARGS2_MACRO__(__VA_ARGS__, __PRINT_FLOAT__, __PRINT_FLOAT_HASH__)(__VA_ARGS__) 
#define DEBUG_HELPER_PRINT_VECTOR(...) __GET_ARGS2_MACRO__(__VA_ARGS__, __PRINT_VECTOR__, __PRINT_VECTOR_HASH__)(__VA_ARGS__) 
#define DEBUG_HELPER_PRINT_ROTATOR(...) __GET_ARGS2_MACRO__(__VA_ARGS__, __PRINT_ROTATOR__, __PRINT_ROTATOR_HASH__)(__VA_ARGS__) 
#define DEBUG_HELPER_PRINT_QUAT(...) __GET_ARGS2_MACRO__(__VA_ARGS__, __PRINT_QUAT__, __PRINT_QUAT_HASH__)(__VA_ARGS__) 

	// Custom Message
	void PrintOnScreen(const FString& Msg, int Key = 0, const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintBool(const FString& StrName, const bool& InBool, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintInt(const FString& StrName, const int& InInt, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintFloat(const FString& StrName, const float& InFloat, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintVector3(const FString& StrName, const FVector& InVector3, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintRotator(const FString& StrName, const FRotator& InRotator, const int& Key = 0, const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintQuaternion(const FString& StrName, const FQuat& InQuaternion, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);

	uint32 Hashing(const FString& Input, int Enhancer = 0);
	
#pragma endregion Screen_Message

}

