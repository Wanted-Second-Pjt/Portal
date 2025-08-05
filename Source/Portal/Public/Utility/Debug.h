#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(CustomDebuggingLog, Type::Log, All);

#define CURRENT_INFO FString(__FUNCTION__) + TEXT("(") + FString::FromInt(__LINE__) + TEXT(")")
#define LOG_THIS_LINE UE_LOG(CustomDebuggingLog, Type::Log, TEXT("%s"), *(CURRENT_INFO))
#define WARNING_THIS_LINE UE_LOG(CustomDebuggingLog, Type::Warning, TEXT("%s"), *(CURRENT_INFO))

// use GetClass()->GetName() return FString
namespace Debug
{
#pragma region UE_Log_Message
	void Log(const FString& Msg);	
	void Warning(const FString& Msg);
	void Error(const FString& Msg);
	void CheckBool(const FString& StrName, const bool& InBool);
	void CheckInt(const FString& StrName, const int& InInt);
	void CheckFloat(const FString& StrName, const float& InFloat, uint32 Decimal = 4);
	void CheckVector3(const FString& StrName, const FVector& InVector3, uint32 Decimal = 4);
	void CheckRotator(const FString& StrName, const FRotator& InRotator, uint32 Decimal = 4);
	void CheckQuaternion(const FString& StrName, const FQuat& InQuaternion, uint32 Decimal = 4);
#pragma endregion UE_Log_Message
	
#pragma region Screen_Debug_Message

	struct FParam_PrintOnScreen
	{
		FString Message = "";
		int Key = 0;
		float Time = 1.0f;
		FColor Color = FColor::Cyan;
		bool bNewerOnTop = true;
	};

	void PrintOnScreen(const FString& Msg, const int& Key = 0, const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintOnScreen(const FParam_PrintOnScreen& Param);
	void PrintBool(const FString& StrName, const bool& InBool, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintInt(const FString& StrName, const int& InInt, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintFloat(const FString& StrName, const float& InFloat, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintVector3(const FString& StrName, const FVector& InVector3, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintRotator(const FString& StrName, const FRotator& InRotator, const int& Key = 0, const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintQuaternion(const FString& StrName, const FQuat& InQuaternion, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
#pragma endregion Screen_Debug_Message

}
