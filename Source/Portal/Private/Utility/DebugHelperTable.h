#pragma once

#include <CoreMinimal.h>
#include "ObjectLifeCycleSingleton.h"

class UDebugHelperVVV final : public TObjectLifeCycleSingleton<UDebugHelperVVV>
{
public:
	struct FParam_PrintOnScreen
	{
		FString Message = "";
		int Key = 0;
		float Time = 1.0f;
		FColor Color = FColor::Cyan;
		bool bNewerOnTop = true;
	};	
	
private:
	virtual bool PreventGetter() override;
	virtual void SetInitTiming() override;
	virtual void SetCleanupTiming() override;
	virtual void SetDestroyTiming() override {};
	
	static void InitData(UWorld* World);
	static void CleanupData(UWorld* World, bool bSessionEnded, bool bCleanUpResources);
	
private:
	static bool bCleaningData;
	
};
