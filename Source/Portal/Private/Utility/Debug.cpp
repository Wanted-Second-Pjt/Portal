#include "Utility/Debug.h"

DEFINE_LOG_CATEGORY(CustomDebuggingLog)

void Debug::Log(const FString& Msg)
{
	UE_LOG(CustomDebuggingLog, Type::Log, TEXT("%s"), *Msg);	
}

void Debug::Warning(const FString& Msg)
{
	UE_LOG(CustomDebuggingLog, Type::Warning, TEXT("%s"), *Msg);
}

void Debug::Error(const FString& Msg)
{
	UE_LOG(CustomDebuggingLog, Type::Error, TEXT("%s"), *Msg);
}

void Debug::CheckBool(const FString& StrName, const bool& InBool)
{
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %hs"), *StrName, InBool ? "True" : "False");
}

void Debug::CheckInt(const FString& StrName, const int& InInt)
{
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %d"), *StrName, InInt);
}

void Debug::CheckFloat(const FString& StrName, const float& InFloat, uint32 Decimal)
{
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %.*f"), *StrName, Decimal, InFloat);
}

void Debug::CheckVector3(const FString& StrName, const FVector& InVector3, uint32 Decimal)
{
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InVector3.X, Decimal, InVector3.Y, Decimal, InVector3.Z);
}

// output: axisX_Roll / axisY_Pitch / axisZ_Yaw
void Debug::CheckRotator(const FString& StrName, const FRotator& InRotator, uint32 Decimal)
{
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InRotator.Roll, Decimal, InRotator.Pitch, Decimal, InRotator.Yaw);
}

void Debug::CheckQuaternion(const FString& StrName, const FQuat& InQuaternion, uint32 Decimal)
{
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InQuaternion.X, Decimal, InQuaternion.Y, Decimal, InQuaternion.Z);
}

void Debug::PrintOnScreen(const FString& Msg, const int& Key, const FColor& Color, const float& Time)
{
	if (GEngine->IsValidLowLevelFast())
	{
		GEngine->AddOnScreenDebugMessage(Key, Time, Color, Msg);
		return;
	}
	Warning("GEngine is not Valid");
}

void Debug::PrintOnScreen(const FParam_PrintOnScreen& Param)
{
	if (GEngine->IsValidLowLevel())
	{
		GEngine->AddOnScreenDebugMessage(Param.Key, Param.Time, Param.Color, Param.Message, Param.bNewerOnTop);
		return;
	}
	Warning("GEngine is not Valid");
}

void Debug::PrintBool(const FString& StrName, const bool& InBool, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + (InBool ? "True" : "False"), Key, Color, Time);
}

void Debug::PrintInt(const FString& StrName, const int& InInt, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + FString::FromInt(InInt), Key, Color, Time);
}

void Debug::PrintFloat(const FString& StrName, const float& InFloat, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + FString::SanitizeFloat(InFloat), Key, Color, Time);
}

void Debug::PrintVector3(const FString& StrName, const FVector& InVector3, const int& Key, const FColor& Color, const float& Time)
{
	
	PrintOnScreen(StrName + ": " + InVector3.ToString(), Key, Color, Time);
}

// output: axisY_Pitch / axisZ_Yaw / axisX_Roll
void Debug::PrintRotator(const FString& StrName, const FRotator& InRotator, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + InRotator.ToString(), Key, Color, Time);
}

void Debug::PrintQuaternion(const FString& StrName, const FQuat& InQuaternion, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + InQuaternion.ToString(), Key, Color, Time);
}
