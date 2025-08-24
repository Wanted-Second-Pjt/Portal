// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

class APlayerController;

enum class EKeyMap : uint8
{	
	W = 0, 				
	A, 				
	S, 				
	D,
	E,
	SpaceBar, 		
	LeftMouseButton,	
	RightMouseButton
};

// Enhanced Input이 하드웨어에서 그대로 받아오기 때문에 
//https://learn.microsoft.com/ko-kr/dotnet/api/system.flagsattribute?view=net-5.0
UENUM(meta = (BitFlags, UseEnumValuesAsMaskVasluesInEditor = "true"))
enum class EPressedKeys : uint8
{
	Default 				= static_cast<uint8>(0) UMETA(Hidden),
	W 						= static_cast<uint8>(1) << 0,
	A 						= static_cast<uint8>(1) << 1,
	S 						= static_cast<uint8>(1) << 2,
	D 						= static_cast<uint8>(1) << 3,
	Interaction				= static_cast<uint8>(1) << 4,
	SpaceBar 				= static_cast<uint8>(1) << 5,
	LeftMouseButton			= static_cast<uint8>(1) << 6,
	RightMouseButton		= static_cast<uint8>(1) << 7,
};
FORCEINLINE uint8 operator<<(const bool& L, EKeyMap&& R)
{ return L << static_cast<uint8>(R); }
FORCEINLINE EPressedKeys operator|( EPressedKeys L,  EPressedKeys R)
{ return static_cast<EPressedKeys>(static_cast<uint8>(L) | static_cast<uint8>(R)); }
FORCEINLINE void operator|=(EPressedKeys& L, const uint8& R)
{ L = static_cast<EPressedKeys>(static_cast<uint8>(L) | R); }
FORCEINLINE EPressedKeys operator&(EPressedKeys L, EPressedKeys R)
{ return static_cast<EPressedKeys>(static_cast<uint8>(L) & static_cast<uint8>(R)); }
FORCEINLINE bool IsPressed(const EPressedKeys& BitMask, EPressedKeys&& BitFlag)
{ return (BitMask & BitFlag) > EPressedKeys::Default; }



#include "ControlComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PORTAL_API UControlComponent : public UActorComponent
{
	GENERATED_BODY()
	
public:
	// Sets default values for this component's properties
	UControlComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	EPressedKeys ReceiveInputs() const;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	FORCEINLINE void SetController(APlayerController* NewController) { PlayerController = NewController; }

	FORCEINLINE void EnableInput(const bool& bInput) {bEnableKeyInput = bInput;}
	
	UFUNCTION(BlueprintCallable)
	FVector2D GetDirection();
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool Moving() const
	{return IsPressed(Pressed, (EPressedKeys::W | EPressedKeys::A | EPressedKeys::S | EPressedKeys::D));}
	FORCEINLINE bool Pause() const
	{return PlayerController->IsInputKeyDown(EKeys::P);}
	
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool PressedMouseLeft() const {return IsPressed(Pressed, EPressedKeys::LeftMouseButton);}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool PressedMouseRight() const {return IsPressed(Pressed, EPressedKeys::RightMouseButton);}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool PressedJump() const {return IsPressed(Pressed, EPressedKeys::SpaceBar);}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool PressedInteract() const {return IsPressed(Pressed, EPressedKeys::SpaceBar);}
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool PressedSpaceBar() const {return IsPressed(Pressed, EPressedKeys::SpaceBar);}
	

	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input, meta = (AllowPrivateAccess = "true", Bitmask, BitmaskEnum = EPressedKeys))
	EPressedKeys Pressed = EPressedKeys::Default;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	APlayerController* PlayerController = nullptr;;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	bool bEnableKeyInput = false;
};
