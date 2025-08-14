#include "DebugHelper.h"

DEFINE_LOG_CATEGORY(CustomDebuggingLog)

void FDebugHelperVVV::Log(const FLocationInfo& Scope, const FString& Msg)
{
	FDebugHelperVVV::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Log, TEXT("%s"), *Msg);
}

void FDebugHelperVVV::Warning(const FLocationInfo& Scope, const FString& Msg)
{
	FDebugHelperVVV::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Warning, TEXT("%s"), *Msg);
}

void FDebugHelperVVV::Error(const FLocationInfo& Scope, const FString& Msg)
{
	FDebugHelperVVV::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Error, TEXT("%s"), *Msg);
}

void FDebugHelperVVV::CheckBool(const FLocationInfo& Scope, const FString& StrName, const bool& InBool)
{
	FDebugHelperVVV::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %hs"), *StrName, InBool ? "True" : "False");
}

void FDebugHelperVVV::CheckInt(const FLocationInfo& Scope, const FString& StrName, const int& InInt)
{
	FDebugHelperVVV::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %d"), *StrName, InInt);
}

// 1 : 10000000 /  -1 : 11111111
void FDebugHelperVVV::CheckEnum(const FLocationInfo& Scope, const FString& StrName, const uint8& InByte)
{
	FDebugHelperVVV::RememberLocation(Scope);
	int Bit = 0;
	for (int i = 0; i < 8; ++i)
	{
		Bit *= 10;
		if (InByte >> i & 1)
			++Bit;
	}
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is masking %08d"), *StrName, Bit);
}

void FDebugHelperVVV::CheckBytesFour(const FLocationInfo& Scope, const FString& StrName, const uint32& InBytes)
{
	FDebugHelperVVV::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("%#08x"), InBytes);
}

void FDebugHelperVVV::CheckPtr(const FLocationInfo& Scope, const FString& StrName, const void* InPtr)
{
	FDebugHelperVVV::RememberLocation(Scope);
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %#p"), *StrName, InPtr);
}

void FDebugHelperVVV::CheckFloat(const FLocationInfo& Scope, const FString& StrName, const float& InFloat, uint32 Decimal)
{
	FDebugHelperVVV::RememberLocation(Scope);
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  %.*f"), *StrName, Decimal, InFloat);
}

void FDebugHelperVVV::CheckVector3(const FLocationInfo& Scope, const FString& StrName, const FVector& InVector3, uint32 Decimal)
{
	FDebugHelperVVV::RememberLocation(Scope);
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InVector3.X, Decimal, InVector3.Y, Decimal, InVector3.Z);
}

// output: axisX_Roll / axisY_Pitch / axisZ_Yaw
void FDebugHelperVVV::CheckRotator(const FLocationInfo& Scope, const FString& StrName, const FRotator& InRotator, uint32 Decimal)
{
	FDebugHelperVVV::RememberLocation(Scope);
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InRotator.Roll, Decimal, InRotator.Pitch, Decimal, InRotator.Yaw);
}

void FDebugHelperVVV::CheckQuaternion(const FLocationInfo& Scope, const FString& StrName, const FQuat& InQuaternion, uint32 Decimal)
{
	FDebugHelperVVV::RememberLocation(Scope);
	if (Decimal > 6) Decimal = 6;
	UE_LOG(CustomDebuggingLog, Type::Display, TEXT("`%s` is  ( %.*f,  %.*f,  %.*f )"), *StrName, Decimal, InQuaternion.X, Decimal, InQuaternion.Y, Decimal, InQuaternion.Z);
}

void FDebugHelperVVV::PrintOnScreen(const FLocationInfo& Scope, const FString& Msg, int Key, const FColor& Color, const float& Time)
{
	FDebugHelperVVV::Get()->RememberLocation(Key, Scope);
	if (GEngine->IsValidLowLevelFast())
	{
		GEngine->AddOnScreenDebugMessage(Key, Time, Color, Msg);
		return;
	}
	Warning(Scope, "GEngine is not Valid");
}


void FDebugHelperVVV::PrintBool(const FLocationInfo& Scope, const FString& StrName, const bool& InBool, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(Scope,StrName + ": " + (InBool ? "True" : "False"), Key, Color, Time);
}

void FDebugHelperVVV::PrintByte(const FLocationInfo& Scope, const FString& StrName, const uint8& InByte, const int& Key,
	const FColor& Color, const float& Time)
{
	FString StrByte = "";
	for (int i = 0; i < 8; ++i) InByte & 1 << i ? StrByte += "1" : StrByte += "0";  
	PrintOnScreen(Scope, StrName + ": " + StrByte, Key, Color, Time);
}

void FDebugHelperVVV::PrintInt(const FLocationInfo& Scope, const FString& StrName, const int& InInt, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(Scope,StrName + ": " + FString::FromInt(InInt), Key, Color, Time);
}

void FDebugHelperVVV::PrintFloat(const FLocationInfo& Scope, const FString& StrName, const float& InFloat, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(Scope,StrName + ": " + FString::SanitizeFloat(InFloat), Key, Color, Time);
}

void FDebugHelperVVV::PrintVector3(const FLocationInfo& Scope, const FString& StrName, const FVector& InVector3, const int& Key, const FColor& Color, const float& Time)
{
	
	PrintOnScreen(Scope,StrName + ": " + InVector3.ToString(), Key, Color, Time);
}

// output: axisY_Pitch / axisZ_Yaw / axisX_Roll
void FDebugHelperVVV::PrintRotator(const FLocationInfo& Scope, const FString& StrName, const FRotator& InRotator, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(Scope,StrName + ": " + InRotator.ToString(), Key, Color, Time);
}

void FDebugHelperVVV::PrintQuaternion(const FLocationInfo& Scope, const FString& StrName, const FQuat& InQuaternion, const int& Key, const FColor& Color, const float& Time)
{
	PrintOnScreen(Scope,StrName + ": " + InQuaternion.ToString(), Key, Color, Time);
}

FDebugHelperVVV::FDebugHelperVVV()
{
}

uint32 FDebugHelperVVV::Hashing(const FString& Input, int Line)
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
		// Uniformed Division Sampling (1Char -> 1Byte -> 16 Bi-bits(2^8) (In _x64) -> 2 Hex-bits(16^2)
		Line %= 256;
		const uint32 Step = Input.Len() * 0.2f;
		const TCHAR* Data = *Input;
		Hash =
			(Line ? Line : Data[Step * 1 + 1]) |
			(Data[Step * 2 + 1] << 8) |
			(Data[Step * 3 + 1] << 16) |
			(Data[Step * 4 + 1] << 24)
		;
		//CheckInt(__SCOPE__, "Line", Line);
		//Line ? Warning(__SCOPE__, FString::Printf(TEXT("%hs:0x%02X, %c:0x%02X, %c:0x%02X, %c:0x%02X"), "Line", Line, Data[Step * 2 + 1], Data[Step * 2 + 1], Data[Step * 3 + 1], Data[Step * 3 + 1], Data[Step * 4 + 1], Data[Step * 4 + 1]))
		//	: Warning(__SCOPE__, FString::Printf(TEXT("%c:0x%02X, %c:0x%02X, %c:0x%02X, %c:0x%02X"), Data[Step * 1 + 1], Data[Step * 1 + 1], Data[Step * 2 + 1], Data[Step * 2 + 1], Data[Step * 3 + 1], Data[Step * 3 + 1], Data[Step * 4 + 1], Data[Step * 4 + 1]));
		//CheckBytesFour(__SCOPE__, Input, Hash);
	}

	return Hash;
	
	// Hashing by ptr
	//return FCrc::MemCrc32(GetData(Input), Input.Len());
}

#pragma region Singleton
bool FDebugHelperVVV::bStopData = false;
TMap<uint32, FString> FDebugHelperVVV::DebuggingLocationMap = TMap<uint32, FString>();

void FDebugHelperVVV::RememberLocation(const uint32& Key, const FString& Location)
{
	DebuggingLocationMap.Add(Key, Location);
}

void FDebugHelperVVV::RememberLocation(const FString& Location)
{
	DebuggingLocationMap.Add(FCrc::StrCrc32(GetData(Location)), Location);
}

bool FDebugHelperVVV::PreventGetter()
{
	return bStopData;
}

void FDebugHelperVVV::SetReStartTiming()
{
	//FWorldDelegates::OnPostWorldCreation.AddStatic(&UDebugHelperVVV::InitData);
}

void FDebugHelperVVV::SetStopTiming()
{
	//FWorldDelegates::OnWorldCleanup.AddStatic(&UDebugHelperVVV::ReStartData);
}

void FDebugHelperVVV::SetDestroyTiming()
{
	
	FEditorDelegates::PrePIEEnded.AddStatic(&FDebugHelperVVV::DestroyData);
}

void FDebugHelperVVV::InitData(UWorld* World)
{
	bStopData = false;
}

void FDebugHelperVVV::StopData(UWorld* World, bool bSessionEnded, bool bCleanUpResources)
{
	bStopData = true;
}

void FDebugHelperVVV::DestroyData(bool bIsSimulating)
{
	for (const TPair<uint32, FString>& It : DebuggingLocationMap)
	{
		UE_LOG(LogPath, Type::Warning, TEXT("%s"), *It.Value);
	}
	
	DebuggingLocationMap.Empty();
}

#pragma endregion Singleton


