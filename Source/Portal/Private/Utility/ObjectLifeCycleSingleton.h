#pragma once

#include <CoreMinimal.h>

template<class TClass>
class TObjectLifeCycleSingleton : public UObject
{	
public:
	UFUNCTION(Category = Singleton)
	static TClass* Get()
	{
		if (bIsShuttingDown)
		{
			return nullptr;
		}
		
		if (Instance == nullptr || IsValid(Instance) == false)
		{
			Instance = NewObject<TClass>();
			// Delete Only GameInstance Shutdown Call
			Instance->AddToRoot();
			
			FCoreDelegates::OnPreExit.AddStatic(&TObjectLifeCycleSingleton::Destroy);
			Instance->SetStopTiming();
			Instance->SetReStartTiming();
			Instance->SetDestroyTiming();
		}

		if (Instance->PreventGetter())
		{
			return nullptr;
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
	UFUNCTION(Category = CanExecute)
	virtual bool PreventGetter() PURE_VIRTUAL(UObjectLifeCycleSingleton::PreventGetter, return false; );
	
	UFUNCTION(Category = Stop)
	virtual void SetStopTiming() PURE_VIRTUAL(UObjectLifeCycleSingleton::SetInitTiming, );
	UFUNCTION(Category = Init)
	virtual void SetReStartTiming() PURE_VIRTUAL(UObjectLifeCycleSingleton::SetInitTiming, );
	UFUNCTION(Category = Stop)
	virtual void SetDestroyTiming() PURE_VIRTUAL(UObjectLifeCycleSingleton::SetDestroyTiming, );
	
private:
	static TObjectPtr<TClass> Instance;
	
	static bool bIsShuttingDown;
};

template<class TClass>
TObjectPtr<TClass> TObjectLifeCycleSingleton<TClass>::Instance = nullptr;
template<class TClass>
bool TObjectLifeCycleSingleton<TClass>::bIsShuttingDown = false;