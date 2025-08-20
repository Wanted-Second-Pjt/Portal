#pragma once

#include "CoreMinimal.h"

class Helper : public UBlueprintFunctionLibrary
{
public:
	template<typename T>
	static T* CreateSceneComponent(AActor* InOwner, FName InComponentName, USceneComponent* InParentComponent = nullptr)
	{
		T* Component = InOwner->CreateDefaultSubobject<T>(InComponentName);
		
		if (IsValid(InParentComponent))
			InOwner->SetRootComponent(Component);
		else
			Component->SetupAttachment(InParentComponent);

		return Component;
	}

	template<typename T>
	static T* CreateActorComponent(AActor* InOwner, FName InComponentName)
	{
		T* Component = InOwner->CreateDefaultSubobject<T>(InComponentName);
		return Component;
	}

	template<typename T>
	static T* GetAssetFromConstructor(FString Path)
	{
		ConstructorHelpers::FObjectFinder<T> Finder(*Path);

		if (Finder.Succeeded())
			return Cast<T>(Finder.Object);
		return nullptr;
	}

	template<typename T>
	static TSubclassOf<T> GetClassFromConstructor(FString Path)
	{
		ConstructorHelpers::FClassFinder<T> Finder(*Path);

		if (Finder.Succeeded())
			return Finder.Class;
		return nullptr;
	}

	// Portal mostly Status(Scale, Extent etc) will Not change.
	static TSubclassOf<AActor> GetPortalClassFromConstructor(const FString& Path = "/Game/Kang/PortalSystem/BP_Portal.BP_Portal")
	{
		
		if (ConstructorHelpers::FClassFinder<AActor> Finder(*Path); !Finder.Succeeded())
		{
			return Finder.Class;
		}
		return nullptr;
	}

	// Return Scale Ratio(float) for Match two Components Origin Sizes from BoxShape. (Which Cant Know By Scale) 
	static bool GetBoxesRatioForScale(const UPrimitiveComponent*& TargetShapeComponent, UPrimitiveComponent*& ToBeModifiedShape)
	{
		if (TargetShapeComponent == nullptr || !IsValid(TargetShapeComponent)
			|| ToBeModifiedShape == nullptr || !IsValid(ToBeModifiedShape))
		{
			return false;
		}
		FBoxSphereBounds TargetBound = TargetShapeComponent->GetLocalBounds();
		FBoxSphereBounds ToBeModifiedBound = ToBeModifiedShape->GetLocalBounds();
		if (TargetBound.ContainsNaN() || ToBeModifiedBound.ContainsNaN())
		{
			return false;
		}
		ToBeModifiedShape->SetRelativeScale3D(
			TargetBound.GetBox().GetSize() / ToBeModifiedBound.GetBox().GetSize()
		);
		return true;
	}

	// no loop. LambdaFunction / World / Call After Seconds (/ &TimerHandle)
	/*static void LambdaTimer(TFunction<void()>&& Functor(), const TObjectPtr<UWorld>& World, const float& InSecond, FTimerHandle* Timer = nullptr)
	{
		if (World == nullptr || !IsValid(World))
		{
			return;
		}
		if (Timer != nullptr && Timer->IsValid())
		{
			return World->GetTimerManager().SetTimer(*Timer, Functor, InSecond, false);
		}
		
		return World->GetTimerManager().SetTimer(*Timer, Functor, InSecond, false);
	}
#define F_TIMER(Seconds, Lambda) LambdaTimer(Lambda, GetWorld(), Seconds)*/
};
