// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Player/PlayerCharacter.h"
#include "GameFramework/PlayerController.h"

#include "Utility/Helper.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Camera/CameraComponent.h"

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
	CameraComp = Helper::CreateSceneComponent<UCameraComponent>(this, "CameraComp", SkeletalComp);

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

	MovementComp->AddInputVector(FVector(ControlComp->GetDirection(), 0));
	if (MovementComp->IsJumpAllowed() && ControlComp->PressedSpaceBar())
	{}
	
	// ToDelegate in ControlComp.. what is faster?
	if (ControlComp->PressedMouseLeft())
	{
		//EquipmentComp->NormalAction(true);
	}
	if (ControlComp->PressedMouseRight())
	{
		//EquipmentComp->NormalAction(false);
	}
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	ControlComp->SetController(CastChecked<APlayerController>(GetController()));
}


