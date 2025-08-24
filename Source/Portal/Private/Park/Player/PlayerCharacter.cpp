// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Player/PlayerCharacter.h"
#include "GameFramework/PlayerController.h"

#include "Utility/Helper.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "Kang/PortalGameInstance.h"

#include "Park/ActorComponents/ControlComponent.h"
#include "Park/SceneComponents/PortalComponent.h"
#include "Park/RelatedPhysics/PlayerMovementComponent.h"
#include "Park/ActorComponents/EquipmentComponent.h"
#include "Park/ActorComponents/ReplicaSynchroComponent.h"


// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComp = Helper::CreateSceneComponent<UCapsuleComponent>(this, "CapsuleComp");
	PortalComp = Helper::CreateSceneComponent<UPortalComponent>(this, "PortalComp", CapsuleComp);
	SkeletalComp = Helper::CreateSceneComponent<USkeletalMeshComponent>(this, "SkeletalMeshComp", CapsuleComp);
	SkeletalComp->SetSkeletalMeshAsset(Helper::GetAssetFromConstructor<USkeletalMesh>(
		"/Game/Park/Character/ControlRig/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple"
	));
	if (CameraComp = Helper::CreateSceneComponent<UCameraComponent>(this, "CameraComp", SkeletalComp);
		IsValid(CameraComp))
	{
		SetupCamera();
	}
	

	ControlComp = Helper::CreateActorComponent<UControlComponent>(this, "ControlComp");
	EquipmentComp = Helper::CreateActorComponent<UEquipmentComponent>(this, "EquipmentComp");
	MovementComp = Helper::CreateActorComponent<UPlayerMovementComponent>(this, "MovementComp");
	ReplicaSynchroComp = Helper::CreateActorComponent<UReplicaSynchroComponent>(this, "ReplicaSynchroComp");
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ControlComp->Pause())
	{
		UPortalGameInstance* PGI = Cast<UPortalGameInstance>(GetGameInstance());
		if (IsValid(PGI))
		{
			PGI->TogglePauseGame();
		}
	}

#pragma region Input
	MovementComp->AddInputVector(FVector(ControlComp->GetDirection(), 0));
	if (MovementComp->IsJumpAllowed() && ControlComp->PressedSpaceBar())
	{
		MovementComp->Jump();
	}
	
	if (EquipmentComp->bEquipSomething && ControlComp->PressedMouseLeft())
	{
		//EquipmentComp->EquipmentAction(true);
	}
	if (EquipmentComp->bEquipSomething && ControlComp->PressedMouseRight())
	{
		//EquipmentComp->NormalAction(false);
	}
#pragma endregion Input
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	ControlComp->SetController(CastChecked<APlayerController>(GetController()));
}

void APlayerCharacter::SetupCamera()
{
	CameraComp->SetFieldOfView(90.f);
}


