#include "Utility/DebugHelperVVV.h"


DEFINE_LOG_CATEGORY(CustomDebuggingLog)

void DEBUG_HELPER_VVV::Log(const FString& Msg)
{
	UE_LOG(CustomDebuggingLog, Type::Log, TEXT("%s"), *Msg);
}

void DEBUG_HELPER_VVV::Warning(const FString& Msg)
{
	UE_LOG(CustomDebuggingLog, Type::Warning, TEXT("%s"), *Msg);
}

void DEBUG_HELPER_VVV::Error(const FString& Msg)
{
	UE_LOG(CustomDebuggingLog, Type::Error, TEXT("%s"), *Msg);
}

void DEBUG_HELPER_VVV::CheckBool(const FString& StrName, const bool& InBool)
{
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %hs"), *StrName, InBool ? "True" : "False");
}

void DEBUG_HELPER_VVV::CheckInt(const FString& StrName, const int& InInt)
{
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %d"), *StrName, InInt);
}

// 1 : 10000000 /  -1 : 11111111
void DEBUG_HELPER_VVV::CheckEnum(const FString& StrName, const uint8& InByte)
{
	int Bit = 0;
	for (int i = 0; i < 8; ++i)
	{
		Bit *= 10;
		if (InByte >> i & 1)
			++Bit;
	}
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is masking %08d"), *StrName, Bit);
}

void DEBUG_HELPER_VVV::CheckBytesFour(const FString& StrName, const uint32& InBytes)
{
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("%#08x"), InBytes);
}

void DEBUG_HELPER_VVV::CheckPtr(const FString& StrName, const void* InPtr)
{
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %#p"), *StrName, InPtr);
}

void DEBUG_HELPER_VVV::CheckFloat(const FString& StrName, const float& InFloat, uint32 Decimal)
{
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %.*f"), *StrName, Decimal, InFloat);
}

void DEBUG_HELPER_VVV::CheckVector3(const FString& StrName, const FVector& InVector3, uint32 Decimal)
{
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InVector3.X, Decimal, InVector3.Y, Decimal, InVector3.Z);
}

// output: axisX_Roll / axisY_Pitch / axisZ_Yaw
void DEBUG_HELPER_VVV::CheckRotator(const FString& StrName, const FRotator& InRotator, uint32 Decimal)
{
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InRotator.Roll, Decimal, InRotator.Pitch, Decimal, InRotator.Yaw);
}

void DEBUG_HELPER_VVV::CheckQuaternion(const FString& StrName, const FQuat& InQuaternion, uint32 Decimal)
{
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InQuaternion.X, Decimal, InQuaternion.Y, Decimal, InQuaternion.Z);
}

void DEBUG_HELPER_VVV::PrintOnScreen(const FString& Msg, int Key, const FColor& Color, const float& Time)
{
	if (Key == 0)
		Key = Hashing(Msg);
	
	if (GEngine->IsValidLowLevelFast())
	{
		GEngine->AddOnScreenDebugMessage(Key, Time, Color, Msg);
		return;
	}
	Warning("GEngine is not Valid");
}


void DEBUG_HELPER_VVV::PrintBool(const FString& StrName, const bool& InBool, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + (InBool ? "True" : "False"), Key, Color, Time);
}

void DEBUG_HELPER_VVV::PrintInt(const FString& StrName, const int& InInt, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + FString::FromInt(InInt), Key, Color, Time);
}

void DEBUG_HELPER_VVV::PrintFloat(const FString& StrName, const float& InFloat, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + FString::SanitizeFloat(InFloat), Key, Color, Time);
}

void DEBUG_HELPER_VVV::PrintVector3(const FString& StrName, const FVector& InVector3, const int& Key, const FColor& Color, const float& Time)
{
	
	PrintOnScreen(StrName + ": " + InVector3.ToString(), Key, Color, Time);
}

// output: axisY_Pitch / axisZ_Yaw / axisX_Roll
void DEBUG_HELPER_VVV::PrintRotator(const FString& StrName, const FRotator& InRotator, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + InRotator.ToString(), Key, Color, Time);
}

void DEBUG_HELPER_VVV::PrintQuaternion(const FString& StrName, const FQuat& InQuaternion, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(StrName + ": " + InQuaternion.ToString(), Key, Color, Time);
}

uint32 DEBUG_HELPER_VVV::Hashing(const FString& Input, int Enhancer)
{
	if (!Enhancer)
		Enhancer %= 256;
	// Uniformed Division Sampling. FName Can have until 31 Words.
	if (Input.Len() > 31 - 3)
	{
		const uint32 Step = Input.Len() * 0.2f;
		const TCHAR* Data = *Input;
		const uint32 Hash =
			Enhancer ? Data[Step * 1 + 1] : Enhancer |
			Data[Step * 2 + 1] << 8 |
			Data[Step * 3 + 1] << 16 |
			Data[Step * 4 + 1] << 24
		;
		//Warning(FString::Printf(TEXT("%c:0x%02X, %c:0x%02X, %c:0x%02X, %c:0x%02X"), Data[Step * 1 + 1], Data[Step * 1 + 1], Data[Step * 2 + 1], Data[Step * 2 + 1], Data[Step * 3 + 1], Data[Step * 3 + 1], Data[Step * 4 + 1], Data[Step * 4 + 1]));
		//CheckBytesFour(Input, Hash);
		return Hash;
	}
	
	// https://dev.epicgames.com/documentation/en-us/unreal-engine/API/Runtime/Core/Misc/FCrc/MemCrc32
	// FName has own Hash Table. but if you write same name, it reWrite previous Msg. 
	return GetTypeHash(FName(*(Input + FString::FromInt(Enhancer))));
	
	// Hashing by ptr
	//return FCrc::MemCrc32(GetData(Input), Input.Len());
}


