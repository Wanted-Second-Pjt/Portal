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

	GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);
	
	GetMesh()->SetSkeletalMeshAsset(Helper::GetAssetFromConstructor<USkeletalMesh>(
			"/Game/Park/Character/ControlRig/Characters/Mannequins/Meshes/SKM_Quinn_Simple.SKM_Quinn_Simple"
	));
	
	if (IsValid(GetMesh()->GetSkeletalMeshAsset()))
	{
		SetupInvisibleMesh();
	
		if (CameraComp = CreateDefaultSubobject<UCameraComponent>("CameraComp");
			IsValid(CameraComp))
		{
			SetupCamera();
			CameraComp->SetupAttachment(GetRootComponent());
			SetupVisibleMesh();
		}
		
		PortalComp = CreateDefaultSubobject<UPortalComponent>("PortalComp");
		PortalComp->SetupAttachment(CameraComp);
	}
	
	ControlComp = Helper::CreateActorComponent<UControlComponent>(this, "ControlComp");
	ReplicaSynchroComp = Helper::CreateActorComponent<UReplicaSynchroComponent>(this, "ReplicaSynchroComp");
	
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add("Player");
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
		//MovementComp->AddInputVector(FVector(ControlComp->GetDirection(), 0));
		AddMovementInput(FVector(ControlComp->GetDirection(), 0));
		if (ControlComp->PressedSpaceBar())
		{
			Jump();
		}
		#pragma endregion Movement

		#pragma region Able Portal
		if (LIKELY(IsValid(PortalComp) && IsValid(CameraComp)))
		{
			PortalComp->GetHitResultFromPlatform(CameraComp->GetComponentLocation(), CameraComp->GetForwardVector());
			
		}
		#pragma endregion Able Portal
	}
	
	
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	APlayerController* PlayerController = CastChecked<APlayerController>(GetController());
	PlayerController->HiddenPrimitiveComponents.Add(GetMesh());
	ControlComp->SetController(PlayerController);
	AutoPossessPlayer = EAutoReceiveInput::Type::Player0;
	//PlayerController->HiddenActors.Add(this);
}

void APlayerCharacter::SetupCamera()
{
	CameraComp->SetFieldOfView(90.f);
	CameraComp->bUsePawnControlRotation	= true;
	bUseControllerRotationPitch = false;  
	bUseControllerRotationYaw = true;     
	bUseControllerRotationRoll = false;
	CameraComp->SetHiddenInGame(true);

	CameraComp->SetWorldLocation(GetMesh()->GetSocketLocation(FName("CameraSocket")));
}

void APlayerCharacter::SetupInvisibleMesh()
{
	GetMesh()->SetCastShadow(true);
	GetMesh()->SetRelativeLocationAndRotation(FVector(0.f, 0.f, -90.f), FRotator(0.f, -90.f, 0.f));
	GetMesh()->SetupAttachment(GetRootComponent());
	if (TSubclassOf<UAnimInstance> TempAnimInstance = Helper::GetClassFromConstructor<UAnimInstance>(TEXT("/Game/Park/Character/ControlRig/Characters/Mannequins/Animations/ABP_Quinn.ABP_Quinn_C")))		
	{
		GetMesh()->SetAnimInstanceClass(TempAnimInstance);
	}
}

void APlayerCharacter::SetupVisibleMesh()
{
	VisibleSkeletalComp = CreateDefaultSubobject<USkeletalMeshComponent> ("VisibleMesh");
	VisibleSkeletalComp->SetupAttachment(CameraComp);
	VisibleSkeletalComp->SetSkeletalMesh(Helper::GetAssetFromConstructor<USkeletalMesh>("/Game/FirstPersonArms/Character/Mesh/SK_Mannequin_Arms.SK_Mannequin_Arms"));
	VisibleSkeletalComp->SetAnimInstanceClass(Helper::GetClassFromConstructor<UAnimInstance>("/Game/FirstPersonArms/Animations/FirstPerson_AnimBP.FirstPerson_AnimBP_C"));
	VisibleSkeletalComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	VisibleSkeletalComp->SetSimulatePhysics(false);
	VisibleSkeletalComp->SetOnlyOwnerSee(true);
	VisibleSkeletalComp->bCastDynamicShadow = false;
	VisibleSkeletalComp->CastShadow = false;
	VisibleSkeletalComp->SetRelativeLocation(FVector(-30.f, 0.f, -151.f));
}


