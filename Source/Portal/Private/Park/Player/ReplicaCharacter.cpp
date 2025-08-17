// Fill out your copyright notice in the Description page of Project Settings.

#include "Park/Player/ReplicaCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"

AReplicaCharacter::AReplicaCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CurrentOpacity = 1.0f;
	TargetOpacity = 1.0f;
	FadeSpeed = 2.0f;
	bIsFading = false;
	bReplicaVisible = true;
	
	CachedMovementSpeed = 0.0f;
	CachedDirection = FVector2D::ZeroVector;
	bCachedOnGround = true;
	bCachedHasWeapon = false;
	
	SetupReplicaDefaults();
}

void AReplicaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeAsReplica();
}

void AReplicaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (bIsFading)
	{
		ProcessFadeEffect(DeltaTime);
	}
}

void AReplicaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (PlayerInputComponent)
	{
		PlayerInputComponent->SetComponentTickEnabled(false);
	}
}


void AReplicaCharacter::InitializeAsReplica()
{
	if (bDisableInputOnSpawn)
	{
		DisableInput(nullptr);

		if (GetController())
		{
			GetController()->UnPossess();
		}
	}

	if (bDisableCollisionOnSpawn)
	{
		SetActorEnableCollision(false);
		
		if (UCapsuleComponent* CapsuleComp = GetCapsuleComponent())
		{
			CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
		
		if (USkeletalMeshComponent* MeshComp = GetMesh())
		{
			MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

	if (bDisableMovementOnSpawn)
	{
		if (UCharacterMovementComponent* MovementComp = GetCharacterMovement())
		{
			MovementComp->SetComponentTickEnabled(false);
			MovementComp->SetUpdatedComponent(nullptr);
			MovementComp->Deactivate();
		}
	}

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{

		MeshComp->SetSimulatePhysics(false);

		MeshComp->SetCastShadow(bEnableShadowCasting);

		MeshComp->SetComponentTickEnabled(true);
		MeshComp->bTickInEditor = false;
	}

	Tags.AddUnique(TEXT("Replica"));
	Tags.AddUnique(TEXT("PortalReplica"));

	SetActorLabel(TEXT("PortalReplica"));
}

void AReplicaCharacter::SetReplicaVisibility(bool bVisible, float InFadeSpeed)
{
	bReplicaVisible = bVisible;
	TargetOpacity = bVisible ? 1.0f : 0.0f;
	FadeSpeed = InFadeSpeed;
	bIsFading = !FMath::IsNearlyEqual(CurrentOpacity, TargetOpacity, 0.01f);
	
	if (!bVisible && FMath::IsNearlyZero(TargetOpacity))
	{
		SetActorHiddenInGame(true);
		CurrentOpacity = 0.0f;
		bIsFading = false;
	}
	else if (bVisible && FMath::IsNearlyZero(CurrentOpacity))
	{
		SetActorHiddenInGame(false);
	}
}

void AReplicaCharacter::SetOpacityImmediate(float Opacity)
{
	CurrentOpacity = FMath::Clamp(Opacity, 0.0f, 1.0f);
	TargetOpacity = CurrentOpacity;
	bIsFading = false;
	
	ApplyOpacityToMaterials(CurrentOpacity);

	if (FMath::IsNearlyZero(CurrentOpacity))
	{
		SetActorHiddenInGame(true);
		bReplicaVisible = false;
	}
	else
	{
		SetActorHiddenInGame(false);
		bReplicaVisible = true;
	}
}

void AReplicaCharacter::UpdateMovementData(float MovementSpeed, const FVector2D& Direction, bool bOnGround)
{
	CachedMovementSpeed = MovementSpeed;
	CachedDirection = Direction;
	bCachedOnGround = bOnGround;

	OnMovementDataUpdated(MovementSpeed, Direction, bOnGround);
}

void AReplicaCharacter::UpdateEquipmentState(bool bHasWeapon, int32 WeaponType)
{
	bCachedHasWeapon = bHasWeapon;
	
	OnEquipmentStateChanged(bHasWeapon, WeaponType);
}

void AReplicaCharacter::TriggerPortalEffect(bool bEntering)
{
	// check about portal enter effect 
	OnPortalEffectTriggered(bEntering);
}

void AReplicaCharacter::ProcessFadeEffect(float DeltaTime)
{
	if (!bIsFading)
	{
		return;
	}
	
	// interpolate opacity
	float PreviousOpacity = CurrentOpacity;
	CurrentOpacity = FMath::FInterpTo(CurrentOpacity, TargetOpacity, DeltaTime, FadeSpeed);
	
	// Mat Transparent.. not use. delete this
	ApplyOpacityToMaterials(CurrentOpacity);
	
	if (FMath::IsNearlyEqual(CurrentOpacity, TargetOpacity, 0.01f))
	{
		CurrentOpacity = TargetOpacity;
		bIsFading = false;
		
		if (FMath::IsNearlyZero(CurrentOpacity))
		{
			SetActorHiddenInGame(true);
		}
	}
	
	// Fade in.. not use.
	if (PreviousOpacity <= 0.01f && CurrentOpacity > 0.01f)
	{
		SetActorHiddenInGame(false);
	}
}

// maybe delete
void AReplicaCharacter::ApplyOpacityToMaterials(float Opacity)
{
	USkeletalMeshComponent* MeshComp = GetMesh();
	if (!MeshComp)
	{
		return;
	}
	
	for (int32 i = 0; i < MeshComp->GetNumMaterials(); ++i)
	{
		UMaterialInterface* Material = MeshComp->GetMaterial(i);
		if (!Material)
		{
			continue;
		}
		UMaterialInstanceDynamic* DynamicMaterial = Cast<UMaterialInstanceDynamic>(Material);
		if (!DynamicMaterial)
		{
			DynamicMaterial = MeshComp->CreateAndSetMaterialInstanceDynamic(i);
		}
		
		if (DynamicMaterial)
		{
			DynamicMaterial->SetScalarParameterValue(OpacityParameterName, Opacity);
		}
	}
}

void AReplicaCharacter::SetupReplicaDefaults()
{
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		MeshComp->SetSimulatePhysics(false);
		
		MeshComp->SetCastShadow(bEnableShadowCasting);
		
		// update smallest
		MeshComp->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::AlwaysTickPoseAndRefreshBones;
	}
	
	if (UCharacterMovementComponent* MovementComp = GetCharacterMovement())
	{
		MovementComp->SetComponentTickEnabled(false);
	}
	
	if (UCapsuleComponent* CapsuleComp = GetCapsuleComponent())
	{
		CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	}
}

