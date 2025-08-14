#include "Park/ActorComponents/ControlComponent.h"
#include "GameFramework/PlayerController.h"
#include "Utility/DebugHelper.h"

DECLARE_DELEGATE(LeftAction);
DECLARE_DELEGATE(RightAction);

UControlComponent::UControlComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
}


// Called when the game starts
void UControlComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	bEnableKeyInput = true;
}


// Called every frame
void UControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	check(PlayerController)
	{ bEnableKeyInput ? Pressed = ReceiveInputs() : Pressed = EPressedKeys::Default; }
	
	DEBUG_HELPER_PRINT_BYTE(static_cast<uint8>(Pressed));
}

EPressedKeys UControlComponent::ReceiveInputs() const
{
	return static_cast<EPressedKeys>(
		(PlayerController->IsInputKeyDown(EKeys::W) << EKeyMap::W) |
		(PlayerController->IsInputKeyDown(EKeys::A) << EKeyMap::A) |
		(PlayerController->IsInputKeyDown(EKeys::S) << EKeyMap::S) |
		(PlayerController->IsInputKeyDown(EKeys::D) << EKeyMap::D) |
		(PlayerController->IsInputKeyDown(EKeys::SpaceBar) << EKeyMap::SpaceBar) |
		(PlayerController->IsInputKeyDown(EKeys::LeftMouseButton) << EKeyMap::LeftMouseButton) |
		(PlayerController->IsInputKeyDown(EKeys::RightMouseButton) << EKeyMap::RightMouseButton)
	);
}

FVector2D UControlComponent::GetDirection()
{
	FVector2D Direction;
	Direction.X = PlayerController->IsInputKeyDown(EKeys::W) - PlayerController->IsInputKeyDown(EKeys::S);
	Direction.Y = PlayerController->IsInputKeyDown(EKeys::D) - PlayerController->IsInputKeyDown(EKeys::A);
	return Direction.GetSafeNormal();
}

void UControlComponent::LeftAction()
{
	
}

void UControlComponent::RightAction()
{
}


