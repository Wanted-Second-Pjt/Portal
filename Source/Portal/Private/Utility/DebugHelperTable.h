#pragma once

#include <CoreMinimal.h>
#include "ObjectLifeCycleSingleton.h"



class UDebugHelperTable final : public TObjectLifeCycleSingleton<UDebugHelperTable>
{
	friend TObjectLifeCycleSingleton;
public:
	static void RememberLocation(const uint32& Key, const FString& Location);
	static void RememberLocation(const FString& Location);
	
private:
	virtual bool PreventGetter() override;
	
	virtual void SetStopTiming() override;
	virtual void SetReStartTiming() override;
	virtual void SetDestroyTiming() override;
	
	static void InitData(UWorld* World);
	static void StopData(UWorld* World, bool bSessionEnded, bool bCleanUpResources);
	static void DestroyData(bool bIsSimulating);
	
private:
	static bool bStopData;
	// (Hash, Location)
	static TMap<uint32, FString> DebuggingLocationMap;
};
