#pragma once

#include <CoreMinimal.h>
#include "ObjectLifeCycleSingleton.h"
#include "DebugMacros.h"


/*
* 1. 
DebugHelper.h 만 include 하시면 사용 가능합니다.
아래에 자주 쓰이는 매크로만 따로 정리해두었습니다. 함수도 물론 쓸 수 있습니다.

* 2. 
컴파일 타임이 조금 늘어납니다.
Source/{MyProjectName}/{MyProjectName}.h 에 추가하면 미리 컴파일된 헤더(pch)로서 사용 가능합니다.
한번만 컴파일 하면 해당 컴퓨터에서는 크게 걱정할 정도로는 오래 안걸립니다.

* 3.
Debug 장소를 기억했다가 게임이 끝날 때 로그로 보여줍니다.
추후 발표용 혹은 배포때는 해당 기록을 보고 지워주시면 됩니다.
게임을 종료하면(정지 버튼 누르면) 테이블 다 초기화됩니다.
이 외에는 런타임에 영향을 주지 않습니다.
 */
DECLARE_LOG_CATEGORY_EXTERN(CustomDebuggingLog, Type::Log, All);
typedef FString FLocationInfo;


/* API
*	Useful Macro. You can " Copy And Paste these with Double-Click "
*	" Write  `debughelpervvv` " Makes Auto Word Completions
*	Scope : Uses " __SCOPE__ "

* Log
DEBUG_HELPER_LOG(Msg)
DEBUG_HELPER_WARNING(Msg)
DEBUG_HELPER_LOG_THIS_LINE
DEBUG_HELPER_WARNING_THIS_LINE
DEBUG_HELPER_LOG_THIS_INSTANCE(this)

DEBUG_HELPER_PRINT_LINE( (Key) )							// if empty args, Print "current line"
DEBUG_HELPER_PRINT_INSTANCE( (instance||this, Key) )		// if empty args, Print "current this"

DEBUG_HELPER_PRINT_STR(InStr (, Key) )
DEBUG_HELPER_PRINT_BOOL(InBool (, Key) )
DEBUG_HELPER_PRINT_INT(InInt (, Key))
DEBUG_HELPER_PRINT_FLOAT(InFloat (, Key) )
DEBUG_HELPER_PRINT_VECTOR(InVec (, Key) )
DEBUG_HELPER_PRINT_ROTATOR(InRot (, Key) )
DEBUG_HELPER_PRINT_QUAT(InQuat (, Key) )

* Print On Screen
* () : Can Use Without ((Argument))
* This : Send To Argument "this" in your instance
* In : Send To Argument "your value" in your class
* Key : If `equal key` is inserted, one Message Cover the other.
* if the Key is empty, Use SelfHashing (Fast, not to worry)
*/

class FDebugHelperVVV final : public TObjectLifeCycleSingleton<FDebugHelperVVV>
{
#pragma region Debug
public:
	static void RememberLocation(const uint32& Key, const FString& Location);
	static void RememberLocation(const FString& Location);

	static uint32 Hashing(const FString& Input, int Line);
private:
	static TMap<uint32, FString> DebuggingLocationMap;

public:
	#pragma region Log_Message
	
	// Custom Message
	void Log(const FLocationInfo& Scope, const FString& Msg);	
	void Warning(const FLocationInfo& Scope, const FString& Msg);
	void Error(const FLocationInfo& Scope, const FString& Msg);
	void CheckBool(const FLocationInfo& Scope, const FString& StrName, const bool& InBool);
	void CheckInt(const FLocationInfo& Scope, const FString& StrName, const int& InInt);
	void CheckEnum(const FLocationInfo& Scope, const FString& StrName, const uint8& InByte);
	void CheckBytesFour(const FLocationInfo& Scope, const FString& StrName, const uint32& InBytes);
	void CheckPtr(const FLocationInfo& Scope, const FString& StrName, const void* InPtr);
	void CheckFloat(const FLocationInfo& Scope, const FString& StrName, const float& InFloat, uint32 Decimal = 4);
	void CheckVector3(const FLocationInfo& Scope, const FString& StrName, const FVector& InVector3, uint32 Decimal = 4);
	void CheckRotator(const FLocationInfo& Scope, const FString& StrName, const FRotator& InRotator, uint32 Decimal = 4);
	void CheckQuaternion(const FLocationInfo& Scope, const FString& StrName, const FQuat& InQuaternion, uint32 Decimal = 4);
	
#pragma endregion Log_Message

#pragma region Screen_Message
	// Custom Message, Scope uses `__SCOPE__`
	void PrintOnScreen(const FLocationInfo& Scope, const FString& Msg, int Key = 0, const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintBool(const FLocationInfo& Scope, const FString& StrName, const bool& InBool, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintInt(const FLocationInfo& Scope, const FString& StrName, const int& InInt, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintFloat(const FLocationInfo& Scope, const FString& StrName, const float& InFloat, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintVector3(const FLocationInfo& Scope, const FString& StrName, const FVector& InVector3, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintRotator(const FLocationInfo& Scope, const FString& StrName, const FRotator& InRotator, const int& Key = 0, const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	void PrintQuaternion(const FLocationInfo& Scope, const FString& StrName, const FQuat& InQuaternion, const int& Key = 0,  const FColor& Color = FColor::Cyan, const float& Time = 1.0f);
	
#pragma endregion Screen_Message
#pragma endregion Debug

	
#pragma region Singleton
private:
	friend class TObjectLifeCycleSingleton;
	FDebugHelperVVV();
	virtual ~FDebugHelperVVV() override = default;
	
	virtual bool PreventGetter() override;
	
	virtual void SetStopTiming() override;
	virtual void SetReStartTiming() override;
	virtual void SetDestroyTiming() override;
	
	static void InitData(UWorld* World);
	static void StopData(UWorld* World, bool bSessionEnded, bool bCleanUpResources);
	static void DestroyData(bool bIsSimulating);
	
private:
	static bool bStopData;
#pragma endregion Singleton
};


#define DEBUG_HELPER_LOG(Msg) if(FDebugHelperVVV::Get()) FDebugHelperVVV::Get()->Log(__SCOPE__, Msg)
#define DEBUG_HELPER_WARNING(Msg) if(FDebugHelperVVV::Get()) FDebugHelperVVV::Get()->Warning(__SCOPE__, Msg)
#define DEBUG_HELPER_LOG_THIS_LINE if(FDebugHelperVVV::Get()) \
	UE_LOG(CustomDebuggingLog, Type::Log, TEXT("%s"), *(__SCOPE__))
#define DEBUG_HELPER_WARNING_THIS_LINE if(FDebugHelperVVV::Get()) \
	UE_LOG(CustomDebuggingLog, Type::Warning, TEXT("%s"), *(__SCOPE__))
#define DEBUG_HELPER_LOG_THIS_INSTANCE if(FDebugHelperVVV::Get()) \
	UE_LOG(CustomDebuggingLog, Type::Log, TEXT("%s"), *(__INSTANCE__(this)))
#define DEBUG_HELPER_LOG_INSTANCE(Instance) if(FDebugHelperVVV::Get()) \
	UE_LOG(CustomDebuggingLog, Type::Log, TEXT("%s"), *(__INSTANCE__(Instance)))

#define DEBUG_HELPER_PRINT_SCREEN(...) if(FDebugHelperVVV::Get()) \
	__MAKE_ARGS_MACRO__(__PRINT_SCREEN__, __GET_ARGS_COUNT__(__VA_ARGS__))(__VA_ARGS__)
// if empty, Print "current line"
#define DEBUG_HELPER_PRINT_LINE(...) if(FDebugHelperVVV::Get()) \
	__MAKE_ARGS_MACRO__(__PRINT_THIS_LINE__, __GET_ARGS_COUNT__(__VA_ARGS__))(__VA_ARGS__)
// if empty, Print "current this instance"
#define DEBUG_HELPER_PRINT_INSTANCE(...) if(FDebugHelperVVV::Get()) \
	__MAKE_ARGS_MACRO__(__PRINT_INSTANCE__, __GET_ARGS_COUNT__(__VA_ARGS__))(__VA_ARGS__)

#define DEBUG_HELPER_PRINT_BOOL(...) if(FDebugHelperVVV::Get()) \
	__MAKE_ARGS_MACRO__(__PRINT_BOOL__, __GET_ARGS_COUNT__(__VA_ARGS__))(__VA_ARGS__)
#define DEBUG_HELPER_PRINT_INT(...) if(FDebugHelperVVV::Get()) \
	__MAKE_ARGS_MACRO__(__PRINT_INT__, __GET_ARGS_COUNT__(__VA_ARGS__))(__VA_ARGS__)
#define DEBUG_HELPER_PRINT_FLOAT(...) if(FDebugHelperVVV::Get()) \
	__MAKE_ARGS_MACRO__(__PRINT_FLOAT__, __GET_ARGS_COUNT__(__VA_ARGS__))(__VA_ARGS__)
#define DEBUG_HELPER_PRINT_VECTOR(...) if(FDebugHelperVVV::Get()) \
	__MAKE_ARGS_MACRO__(__PRINT_VECTOR__, __GET_ARGS_COUNT__(__VA_ARGS__))(__VA_ARGS__) 
#define DEBUG_HELPER_PRINT_ROTATOR(...) if(FDebugHelperVVV::Get()) \
	__MAKE_ARGS_MACRO__(__PRINT_ROTATOR__, __GET_ARGS_COUNT__(__VA_ARGS__))(__VA_ARGS__) 
#define DEBUG_HELPER_PRINT_QUAT(...) if(FDebugHelperVVV::Get()) \
	__MAKE_ARGS_MACRO__(__PRINT_QUAT__, __GET_ARGS_COUNT__(__VA_ARGS__))(__VA_ARGS__)