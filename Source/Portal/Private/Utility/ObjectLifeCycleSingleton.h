#pragma once

#include <CoreMinimal.h>

template<class Class>
class TObjectLifeCycleSingleton : public UObject
{	
public:
	UFUNCTION(Category = Singleton)
	static Class* Get()
	{
		if (bIsShuttingDown && PreventGetter())
		{
			return nullptr;
		}
		
		if (Instance == nullptr || IsValid(Instance) == false)
		{
			Instance = NewObject<Class>();
			// Delete Only GameInstance Shutdown Call
			Instance->AddToRoot();
			
			FCoreDelegates::OnPreExit.AddStatic(&TObjectLifeCycleSingleton::Destroy);
			SetInitTiming();
			SetCleanupTiming();
			SetDestroyTiming();
		}
		
		return Instance;
	}

	UFUNCTION(Category = Singleton)
	static void Destroy()
	{
		bIsShuttingDown = true;
		if (Instance != nullptr && IsValid(Instance))
		{
			Instance->RemoveFromRoot();
			Instance = nullptr;
		}
	}

protected:
	UFUNCTION(Category = Singleton)
	virtual bool PreventGetter() PURE_VIRTUAL(UObjectLifeCycleSingleton::PreventGetter, return false; );
	
	UFUNCTION(Category = Singleton)
	virtual void SetInitTiming() PURE_VIRTUAL(UObjectLifeCycleSingleton::SetInitTiming, );
	UFUNCTION(Category = Singleton)
	virtual void SetCleanupTiming() PURE_VIRTUAL(UObjectLifeCycleSingleton::SetInitTiming, );
	UFUNCTION(Category = Singleton)
	virtual void SetDestroyTiming() PURE_VIRTUAL(UObjectLifeCycleSingleton::SetDestroyTiming, );
	
private:
	static TSubclassOf<Class> Instance;
	
	static bool bIsShuttingDown;
};

template<class Class>
TSubclassOf<Class> TObjectLifeCycleSingleton<Class>::Instance = nullptr;
template<class Class>
bool TObjectLifeCycleSingleton<Class>::bIsShuttingDown = false;