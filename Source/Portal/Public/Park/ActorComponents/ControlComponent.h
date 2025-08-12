// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

class APlayerController;

//https://learn.microsoft.com/ko-kr/dotnet/api/system.flagsattribute?view=net-5.0
UENUM(meta = (BitFlags, UseEnumValuesAsMaskVasluesInEditor = "true"))
enum class EPressedKeys : uint8
{
	Default 		= 1 << 0 UMETA(Hidden),
	W 				= 1 << 1,
	A 				= 1 << 2,
	S 				= 1 << 3,
	D 				= 1 << 4,
	SpaceBar 		= 1 << 5,
	Left 			= 1 << 6,
	Right 			= 1 << 7,
};

#include "ControlComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTAL_API UControlComponent : public UActorComponent
{
	GENERATED_BODY()

	// ToByteFlag

	
	
public:
	// Sets default values for this component's properties
	UControlComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE void SetController(APlayerController* NewController) { PlayerController = NewController; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = EPressedKeys))
	EPressedKeys Pressed = EPressedKeys::Default;
	//inline EPressedKeys& operator|=(EPressedKeys& Lhs, bool Rhs) { return Lhs = Lhs | Rhs ? : ;}

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	APlayerController* PlayerController = nullptr;;
	
};
