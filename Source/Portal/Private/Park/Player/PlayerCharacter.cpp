// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Player/PlayerCharacter.h"

#include "PortalWeaponComponent.h"
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
	SetRootComponent(CapsuleComp);
	CapsuleComp->SetCapsuleHalfHeight(100.f);
	CapsuleComp->SetCapsuleRadius(40.f);
	CapsuleComp->SetLineThickness(1.0f);

	if (SkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComp");
		IsValid(SkeletalComp))
	{
		SkeletalComp->SetSkeletalMeshAsset(Helper::GetAssetFromConstructor<USkeletalMesh>(
			"/Game/Park/Character/ControlRig/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple"
		));
		SkeletalComp->SetupAttachment(CapsuleComp);
		SkeletalComp->SetRelativeLocation(FVector(0.f, 0.f, -90.f));
	}
	
	if (CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
		IsValid(CameraComp))
	{
		SetupCamera();
		CameraComp->SetupAttachment(SkeletalComp, FName("CameraSocket"));
	}

	if (TSubclassOf<UAnimInstance> TempAnimInstance = Helper::GetClassFromConstructor<UAnimInstance>(TEXT("/Game/Park/Character/ControlRig/Characters/Mannequins/Animations/ABP_Quinn.ABP_Quinn_C")))		
	{
		SkeletalComp->SetAnimInstanceClass(TempAnimInstance);
	}
	PortalComp = CreateDefaultSubobject<UPortalComponent>("PortalComp");
	PortalComp->SetupAttachment(CameraComp);
	

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

	
	
	if (ControlComp->GetEnableInput())
	{
		#pragma region Movement
		MovementComp->AddInputVector(FVector(ControlComp->GetDirection(), 0));
		if (ControlComp->PressedSpaceBar())
		{
			MovementComp->Jump();
		}
		#pragma endregion Movement

		#pragma region Able Portal
		if (LIKELY(IsValid(PortalComp) && IsValid(CameraComp)))
		{
			if (IsValid(WeaponComp))
			{
				const bool bEnablePortal = PortalComp->GetHitResultFromPlatform(CameraComp->GetComponentLocation(), CameraComp->GetForwardVector());
				if (EquipmentComp->bEquipSomething && ControlComp->PressedMouseLeft())
				{
					WeaponComp->Fire();
				}
				if (EquipmentComp->bEquipSomething && ControlComp->PressedMouseRight())
				{
					WeaponComp->Fire();
				}
				
			}
		}
		#pragma endregion Able Portal
	}
	
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	ControlComp->SetController(PlayerController);
	AutoPossessPlayer = EAutoReceiveInput::Type::Player0;
	//PlayerController->HiddenActors.Add(this);
}

void APlayerCharacter::SetupCamera()
{
	CameraComp->SetFieldOfView(90.f);
}


