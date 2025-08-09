#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(CustomDebuggingLog, Type::Log, All);

/*
*	Useful Macro. You can Copy And Paste these
*
DEBUG_HELPER_LOG_THIS_LINE
DEBUG_HELPER_WARNING_THIS_LINE
DEBUG_HELPER_LOG_THIS_INSTANCE(this)

DEBUG_HELPER_PRINT_THIS_LINE(Key)
DEBUG_HELPER_PRINT_THIS_INSTANCE(this, Key)

DEBUG_HELPER_PRINT_BOOL(InBool, Key)
DEBUG_HELPER_PRINT_INT(InInt, Key)
DEBUG_HELPER_PRINT_FLOAT(InFloat, Key)
DEBUG_HELPER_PRINT_VECTOR(InVec, Key)
DEBUG_HELPER_PRINT_ROTATOR(InRot, Key)
DEBUG_HELPER_PRINT_QUAT(InQuat, Key)

* This : Send To Argument "this" in your class
* In : Send To Argument "your value" in your class
* Key : You must Insert Key. if equal key is inserted, one Message Cover the other.
*/


namespace DEBUG_HELPER
{
#pragma region Log_Message

#define DEBUG_HELPER_LOG_THIS_LINE \
	UE_LOG(CustomDebuggingLog, Type::Log, TEXT("%s"), *(__CURRENT_LINE__))
#define DEBUG_HELPER_WARNING_THIS_LINE \
	UE_LOG(CustomDebuggingLog, Type::Warning, TEXT("%s"), *(__CURRENT_LINE__))
#define DEBUG_HELPER_LOG_THIS_INSTANCE(This) \
	UE_LOG(CustomDebuggingLog, Type::Log, \
	TEXT("%s, %s"), *(__CURRENT_INSTANCE__(This)), *(__CURRENT_LINE__))
	
	// Custom Message
	void Log(const FString& Msg);	
	void Warning(const FString& Msg);
	void Error(const FString& Msg);
	void CheckBool(const FString& StrName, const bool& InBool);
	void CheckInt(const FString& StrName, const int& InInt);
	void CheckFloat(const FString& StrName, const float& InFloat, uint32 Decimal = 4);
	void CheckVector3(const FString& StrName, const FVector& InVector3, uint32 Decimal = 4);
	void CheckRotator(const FString& StrName, const FRotator& InRotator, uint32 Decimal = 4);
	void CheckQuaternion(const FString& StrName, const FQuat& InQuaternion, uint32 Decimal = 4);
	
#pragma endregion Log_Message
	
#pragma region Screen_Message

	struct FParam_PrintOnScreen
	{
		FString Message = "";
		int Key = 0;
		float Time = 1.0f;
		FColor Color = FColor::Cyan;
		bool bNewerOnTop = true;
	};

	// Useful Macros
#define DEBUG_HELPER_PRINT_THIS_LINE(Key) DEBUG_HELPER::PrintOnScreen(__CURRENT_L__, Key)
#define DEBUG_HELPER_PRINT_THIS_INSTANCE(This, Key) \
	DEBUG_HELPER::PrintOnScreen(__CURRENT_I__(This) + " : " + __CURRENT_L__, Key)
#define DEBUG_HELPER_PRINT_BOOL(InBool, Key) DEBUG_HELPER::PrintBool(__STRINGYFY__(InBool), InBool, Key)
#define DEBUG_HELPER_PRINT_INT(InInt, Key) DEBUG_HELPER::PrintInt(__STRINGYFY__(InInt), InInt, Key)
#define DEBUG_HELPER_PRINT_FLOAT(InFloat, Key) DEBUG_HELPER::PrintFloat(__STRINGYFY__(InFloat), InFloat, Key)
#define DEBUG_HELPER_PRINT_VECTOR(InVec, Key) DEBUG_HELPER::PrintVector3(__STRINGYFY__(InVec), InVec, Key)
#define DEBUG_HELPER_PRINT_ROTATOR(InRot, Key) DEBUG_HELPER::PrintRotator(__STRINGYFY__(InRot), InRot, Key)
#define DEBUG_HELPER_PRINT_QUAT(InQuat, Key) DEBUG_HELPER::PrintQuaternion(__STRINGYFY__(InQuat), InQuat, Key)

	// Custom Message
	void PrintOnScreen(const FString& Msg, const int& Key = 0, const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintOnScreen(const FParam_PrintOnScreen& Param);
	void PrintBool(const FString& StrName, const bool& InBool, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintInt(const FString& StrName, const int& InInt, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintFloat(const FString& StrName, const float& InFloat, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintVector3(const FString& StrName, const FVector& InVector3, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintRotator(const FString& StrName, const FRotator& InRotator, const int& Key = 0, const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintQuaternion(const FString& StrName, const FQuat& InQuaternion, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	
#pragma endregion Screen_Message

}


#pragma region For_Inline_Macro  // Not Important
#define __CURRENT_L__ FString::Printf(TEXT("%hs, (%d)"), __FUNCTION__, __LINE__)
#define __CURRENT_I__(This) (IsValid(This) ? This->GetName() : "")
#define __STRINGYFY__(x) FString(#x)
#pragma endregion For_Inline_Macro