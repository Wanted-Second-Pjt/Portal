#include "Park/ActorComponents/ControlComponent.h"
#include "GameFramework/PlayerController.h"

ENUM_CLASS_FLAGS(EPressedKeys);

UControlComponent::UControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UControlComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	check(PlayerController)
	
	// if (Pressed |= PlayerController->IsInputKeyDown(EKeys::W) << 1)
	// 	Pressed |= EPressedKeys::W;
	// EKeys::W;
}


