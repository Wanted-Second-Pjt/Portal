#include "Utility/DebugHelper.h"

DEFINE_LOG_CATEGORY(CustomDebuggingLog)


void DEBUG_HELPER::Log(const FString& Msg)
{
	UE_LOG(CustomDebuggingLog, Type::Log, TEXT("%s"), *Msg);
	
	
}

void DEBUG_HELPER::Warning(const FString& Msg)
{
	UE_LOG(CustomDebuggingLog, Type::Warning, TEXT("%s"), *Msg);
}

void DEBUG_HELPER::Error(const FString& Msg)
{
	UE_LOG(CustomDebuggingLog, Type::Error, TEXT("%s"), *Msg);
}

void DEBUG_HELPER::CheckBool(const FString& StrName, const bool& InBool)
{
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %hs"), *StrName, InBool ? "True" : "False");
}

void DEBUG_HELPER::CheckInt(const FString& StrName, const int& InInt)
{
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %d"), *StrName, InInt);
}

void DEBUG_HELPER::CheckFloat(const FString& StrName, const float& InFloat, uint32 Decimal)
{
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %.*f"), *StrName, Decimal, InFloat);
}

void DEBUG_HELPER::CheckVector3(const FString& StrName, const FVector& InVector3, uint32 Decimal)
{
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InVector3.X, Decimal, InVector3.Y, Decimal, InVector3.Z);
}

// output: axisX_Roll / axisY_Pitch / axisZ_Yaw
void DEBUG_HELPER::CheckRotator(const FString& StrName, const FRotator& InRotator, uint32 Decimal)
{
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InRotator.Roll, Decimal, InRotator.Pitch, Decimal, InRotator.Yaw);
}

void DEBUG_HELPER::CheckQuaternion(const FString& StrName, const FQuat& InQuaternion, uint32 Decimal)
{
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InQuaternion.X, Decimal, InQuaternion.Y, Decimal, InQuaternion.Z);
}

void DEBUG_HELPER::PrintOnScreen(const FString& Msg, const int& Key, const FColor& Color, const float& Time)
{
	if (GEngine->IsValidLowLevelFast())
	{
		GEngine->AddOnScreenDebugMessage(Key, Time, Color, Msg);
		return;
	}
	Warning("GEngine is not Valid");
}

void DEBUG_HELPER::PrintOnScreen(const FParam_PrintOnScreen& Param)
{
	if (GEngine->IsValidLowLevel())
	{
		GEngine->AddOnScreenDebugMessage(Param.Key, Param.Time, Param.Color, Param.Message, Param.bNewerOnTop);
		return;
	}
	Warning("GEngine is not Valid");
}

void DEBUG_HELPER::PrintBool(const FString& StrName, const bool& InBool, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + (InBool ? "True" : "False"), Key, Color, Time);
}

void DEBUG_HELPER::PrintInt(const FString& StrName, const int& InInt, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + FString::FromInt(InInt), Key, Color, Time);
}

void DEBUG_HELPER::PrintFloat(const FString& StrName, const float& InFloat, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + FString::SanitizeFloat(InFloat), Key, Color, Time);
}

void DEBUG_HELPER::PrintVector3(const FString& StrName, const FVector& InVector3, const int& Key, const FColor& Color, const float& Time)
{
	
	PrintOnScreen(StrName + ": " + InVector3.ToString(), Key, Color, Time);
}

// output: axisY_Pitch / axisZ_Yaw / axisX_Roll
void DEBUG_HELPER::PrintRotator(const FString& StrName, const FRotator& InRotator, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + InRotator.ToString(), Key, Color, Time);
}

void DEBUG_HELPER::PrintQuaternion(const FString& StrName, const FQuat& InQuaternion, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + InQuaternion.ToString(), Key, Color, Time);
}
