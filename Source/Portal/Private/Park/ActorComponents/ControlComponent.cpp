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
	
	bEnableKeyInput = true;
	//if ()
	PlayerController->SetInputMode(FInputModeGameOnly());
	PlayerController->SetShowMouseCursor(false);
	PlayerController->SetMouseLocation(0.0f, 0.0f);
	PlayerController->PlayerCameraManager->ViewPitchMin = MinPitchAngle;
	PlayerController->PlayerCameraManager->ViewPitchMax = MaxPitchAngle;
}


// Called every frame
void UControlComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	check(PlayerController)
	{
		if (bEnableKeyInput)
		{
			Pressed = ReceiveInputs();
			ApplyMouseInput();
		}
		else
		{
			Pressed = EPressedKeys::Default;
		}
	}

	DEBUG_HELPER_PRINT_BYTE(static_cast<uint8>(Pressed));
}

EPressedKeys UControlComponent::ReceiveInputs()
{
	PrevPressed = Pressed;
	return static_cast<EPressedKeys>(
		(PlayerController->IsInputKeyDown(EKeys::W) << EKeyMap::W) |
		(PlayerController->IsInputKeyDown(EKeys::A) << EKeyMap::A) |
		(PlayerController->IsInputKeyDown(EKeys::S) << EKeyMap::S) |
		(PlayerController->IsInputKeyDown(EKeys::D) << EKeyMap::D) |
		(PlayerController->IsInputKeyDown(EKeys::E) << EKeyMap::E) |
		(PlayerController->IsInputKeyDown(EKeys::SpaceBar) << EKeyMap::SpaceBar) |
		(PlayerController->IsInputKeyDown(EKeys::LeftMouseButton) << EKeyMap::LeftMouseButton) |
		(PlayerController->IsInputKeyDown(EKeys::RightMouseButton) << EKeyMap::RightMouseButton)
	);
}

FVector2D UControlComponent::GetDirection()
{
	FVector Direction = FVector::ZeroVector;
	Direction.X = IsPressed(Pressed, EPressedKeys::W) - IsPressed(Pressed , EPressedKeys::S);
	Direction.Y = IsPressed(Pressed , EPressedKeys::D) - IsPressed(Pressed, EPressedKeys::A);
	
	APawn* Pawn = PlayerController->GetPawn();
	return FVector2D(Pawn->GetActorTransform().TransformVector(Direction).GetSafeNormal());
	
	// if (Direction.IsNearlyZero())
	// {
	// 	return FVector2D::ZeroVector;
	// }
	//
	// Direction = Direction.GetSafeNormal();
	//
	// if (APawn* Pawn = PlayerController->GetPawn())
	// {
	// 	float Yaw = FMath::DegreesToRadians(Pawn->GetControlRotation().Yaw);
	// 	float CosYaw = FMath::Cos(Yaw);
	// 	float SinYaw = FMath::Sin(Yaw);
	//
	// 	FVector2D RotatedDirection;
	// 	RotatedDirection.X = Direction.X * CosYaw - Direction.Y * SinYaw;
	// 	RotatedDirection.Y = Direction.X * SinYaw + Direction.Y * CosYaw;
	//
	// 	return RotatedDirection;
	// }
	//
	// return Direction;
}

void UControlComponent::ApplyMouseInput()
{
	float DeltaX = 0, DeltaY = 0;
	PlayerController->GetInputMouseDelta(DeltaX, DeltaY);
	DeltaX *= MouseSensitivityX;
	DeltaY *= MouseSensitivityY;
	DEBUG_HELPER_PRINT_FLOAT(DeltaX);
	DEBUG_HELPER_PRINT_FLOAT(DeltaY);
	if (FMath::IsNearlyZero(DeltaX) && FMath::IsNearlyZero(DeltaY))
	{
		return;
	}
	
	if (!FMath::IsNearlyZero(DeltaX))
	{
		PlayerController->AddYawInput(DeltaX);
	}
	if (!FMath::IsNearlyZero(DeltaY))
	{
		if (bInvertMouseY)
		{
			DeltaY = -DeltaY;
		}
		PlayerController->AddPitchInput(-DeltaY);
	}

	

	

}
