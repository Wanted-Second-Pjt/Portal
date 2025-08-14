#pragma once

#include <CoreMinimal.h>

#include "SComponentClassCombo.h"

template<class IC>
class TObjectLifeCycleSingleton
{
	static IC* Instance;
	static bool bIsShuttingDown;
public:
	static IC* Get()
	{
		if (!GEngine || !IsInGameThread())
		{
			return nullptr;
		}
		if (bIsShuttingDown)
		{
			return nullptr;
		}
		
		
		if (Instance == nullptr)
		{
			Instance = new IC();
			
			FCoreDelegates::OnPreExit.AddStatic(&TObjectLifeCycleSingleton::Destroy);
			Instance->SetStopTiming();
			Instance->SetReStartTiming();
			Instance->SetDestroyTiming();
		}
		if (Instance != nullptr && !Instance->PreventGetter())
		{
			return Instance;
		}
		
		return nullptr;
	}

	static void Destroy()
	{
		bIsShuttingDown = true;
		if (Instance != nullptr)
		{
			delete Instance;
			Instance = nullptr;
		}
	}

	TObjectLifeCycleSingleton(const TObjectLifeCycleSingleton&) = delete;
	TObjectLifeCycleSingleton& operator=(const TObjectLifeCycleSingleton&) = delete;
	TObjectLifeCycleSingleton(TObjectLifeCycleSingleton&&) = delete;
	TObjectLifeCycleSingleton& operator=(TObjectLifeCycleSingleton&&) = delete;

protected:
	TObjectLifeCycleSingleton() = default;
	virtual ~TObjectLifeCycleSingleton() = default;
	
	virtual bool PreventGetter() = 0;
	
	virtual void SetStopTiming() = 0;
	virtual void SetReStartTiming() = 0;
	virtual void SetDestroyTiming() = 0;
};

template<class IC>
IC* TObjectLifeCycleSingleton<IC>::Instance = nullptr;
template<class IC>
bool TObjectLifeCycleSingleton<IC>::bIsShuttingDown = false;