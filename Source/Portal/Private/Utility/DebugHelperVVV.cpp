#include "Utility/DebugHelperVVV.h"

#include "DebugHelperTable.h"

DEFINE_LOG_CATEGORY(CustomDebuggingLog)

void DEBUG_HELPER_VVV::Log(const FLocationInfo& Scope, const FString& Msg)
{
	UDebugHelperTable::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Log, TEXT("%s"), *Msg);
}

void DEBUG_HELPER_VVV::Warning(const FLocationInfo& Scope, const FString& Msg)
{
	UDebugHelperTable::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Warning, TEXT("%s"), *Msg);
}

void DEBUG_HELPER_VVV::Error(const FLocationInfo& Scope, const FString& Msg)
{
	UDebugHelperTable::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Error, TEXT("%s"), *Msg);
}

void DEBUG_HELPER_VVV::CheckBool(const FLocationInfo& Scope, const FString& StrName, const bool& InBool)
{
	UDebugHelperTable::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %hs"), *StrName, InBool ? "True" : "False");
}

void DEBUG_HELPER_VVV::CheckInt(const FLocationInfo& Scope, const FString& StrName, const int& InInt)
{
	UDebugHelperTable::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %d"), *StrName, InInt);
}

// 1 : 10000000 /  -1 : 11111111
void DEBUG_HELPER_VVV::CheckEnum(const FLocationInfo& Scope, const FString& StrName, const uint8& InByte)
{
	UDebugHelperTable::RememberLocation(Scope);
	int Bit = 0;
	for (int i = 0; i < 8; ++i)
	{
		Bit *= 10;
		if (InByte >> i & 1)
			++Bit;
	}
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is masking %08d"), *StrName, Bit);
}

void DEBUG_HELPER_VVV::CheckBytesFour(const FLocationInfo& Scope, const FString& StrName, const uint32& InBytes)
{
	UDebugHelperTable::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("%#08x"), InBytes);
}

void DEBUG_HELPER_VVV::CheckPtr(const FLocationInfo& Scope, const FString& StrName, const void* InPtr)
{
	UDebugHelperTable::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %#p"), *StrName, InPtr);
}

void DEBUG_HELPER_VVV::CheckFloat(const FLocationInfo& Scope, const FString& StrName, const float& InFloat, uint32 Decimal)
{
	UDebugHelperTable::RememberLocation(Scope);
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %.*f"), *StrName, Decimal, InFloat);
}

void DEBUG_HELPER_VVV::CheckVector3(const FLocationInfo& Scope, const FString& StrName, const FVector& InVector3, uint32 Decimal)
{
	UDebugHelperTable::RememberLocation(Scope);
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InVector3.X, Decimal, InVector3.Y, Decimal, InVector3.Z);
}

// output: axisX_Roll / axisY_Pitch / axisZ_Yaw
void DEBUG_HELPER_VVV::CheckRotator(const FLocationInfo& Scope, const FString& StrName, const FRotator& InRotator, uint32 Decimal)
{
	UDebugHelperTable::RememberLocation(Scope);
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InRotator.Roll, Decimal, InRotator.Pitch, Decimal, InRotator.Yaw);
}

void DEBUG_HELPER_VVV::CheckQuaternion(const FLocationInfo& Scope, const FString& StrName, const FQuat& InQuaternion, uint32 Decimal)
{
	UDebugHelperTable::RememberLocation(Scope);
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InQuaternion.X, Decimal, InQuaternion.Y, Decimal, InQuaternion.Z);
}

void DEBUG_HELPER_VVV::PrintOnScreen(const FLocationInfo& Scope, const FString& Msg, int Key, const FColor& Color, const float& Time)
{
	UDebugHelperTable::Get()->RememberLocation(Key, Scope);
	if (GEngine->IsValidLowLevelFast())
	{
		GEngine->AddOnScreenDebugMessage(Key, Time, Color, Msg);
		return;
	}
	Warning(Scope, "GEngine is not Valid");
}


void DEBUG_HELPER_VVV::PrintBool(const FLocationInfo& Scope, const FString& StrName, const bool& InBool, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(Scope,StrName + ": " + (InBool ? "True" : "False"), Key, Color, Time);
}

void DEBUG_HELPER_VVV::PrintInt(const FLocationInfo& Scope, const FString& StrName, const int& InInt, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(Scope,StrName + ": " + FString::FromInt(InInt), Key, Color, Time);
}

void DEBUG_HELPER_VVV::PrintFloat(const FLocationInfo& Scope, const FString& StrName, const float& InFloat, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(Scope,StrName + ": " + FString::SanitizeFloat(InFloat), Key, Color, Time);
}

void DEBUG_HELPER_VVV::PrintVector3(const FLocationInfo& Scope, const FString& StrName, const FVector& InVector3, const int& Key, const FColor& Color, const float& Time)
{
	
	PrintOnScreen(Scope,StrName + ": " + InVector3.ToString(), Key, Color, Time);
}

// output: axisY_Pitch / axisZ_Yaw / axisX_Roll
void DEBUG_HELPER_VVV::PrintRotator(const FLocationInfo& Scope, const FString& StrName, const FRotator& InRotator, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(Scope,StrName + ": " + InRotator.ToString(), Key, Color, Time);
}

void DEBUG_HELPER_VVV::PrintQuaternion(const FLocationInfo& Scope, const FString& StrName, const FQuat& InQuaternion, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(Scope,StrName + ": " + InQuaternion.ToString(), Key, Color, Time);
}

uint32 DEBUG_HELPER_VVV::Hashing(const FString& Input, int Line)
{
	uint32 Hash;
	
	if (Input.Len() < 29)
	{
		// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/Misc/FCrc/MemCrc32
		// UObject, FName, FString has own Type Hash. but if you write same name, it reWrite previous Msg.
		Hash = GetTypeHash(Input + FString::FromInt(Line));
	}
	else
	{
		// Uniformed Division Sampling (4Char -> 4Bytes -> 32 Bi-bits -> 4 Hex-bits
		Line %= 256;
		const uint32 Step = Input.Len() * 0.2f;
		const TCHAR* Data = *Input;
		Hash =
			Line ? Data[Step * 1 + 1] : Line |
			Data[Step * 2 + 1] << 8 |
			Data[Step * 3 + 1] << 16 |
			Data[Step * 4 + 1] << 24
		;
		//Warning(FString::Printf(TEXT("%c:0x%02X, %c:0x%02X, %c:0x%02X, %c:0x%02X"), Data[Step * 1 + 1], Data[Step * 1 + 1], Data[Step * 2 + 1], Data[Step * 2 + 1], Data[Step * 3 + 1], Data[Step * 3 + 1], Data[Step * 4 + 1], Data[Step * 4 + 1]));
		//CheckBytesFour(Input, Hash);
	}

	return Hash;
	
	// Hashing by ptr
	//return FCrc::MemCrc32(GetData(Input), Input.Len());
}


