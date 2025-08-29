// Fill out your copyright notice in the Description page of Project Settings.

#include "Park/Player/ReplicaCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Engine/Engine.h"
#include "Park/ActorComponents/ReplicaSynchroComponent.h"
#include "Park/Animation/ReplicaAnimInstance.h"

AReplicaCharacter::AReplicaCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	bDisableCollisionOnSpawn = true;
	bDisableInputOnSpawn = true;
	bDisableMovementOnSpawn = true;
	bEnableShadowCasting = true;
	bReplicaVisible = false;  // debug용
	AnimationData = FReplicaAnimationData();
	
	SetupReplicaDefaults();
}

void AReplicaCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeAsReplica();
}

/*
void AReplicaCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
*/

void AReplicaCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (IsValid(PlayerInputComponent))
	{
		PlayerInputComponent->SetComponentTickEnabled(false);
	}
	if (bDisableInputOnSpawn)
	{
		DisableInput(nullptr);

		if (GetController())
		{
			GetController()->UnPossess();
		}
	}
}


void AReplicaCharacter::InitializeAsReplica()
{
	// In Setup PlayerInput Comp
	// if (bDisableInputOnSpawn)
	// {
	// 	DisableInput(nullptr);
	//
	// 	if (GetController())
	// 	{
	// 		GetController()->UnPossess();
	// 	}
	// }

	if (bDisableCollisionOnSpawn)
	{
		SetActorEnableCollision(false);
		
		if (UCapsuleComponent* CapsuleComp = GetCapsuleComponent())
		{
			UE_LOG(LogTemp, Display, TEXT("CapsuleComponent is now null"));
			CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}
	}

	if (bDisableMovementOnSpawn)
	{
		if (UCharacterMovementComponent* MovementComp = GetCharacterMovement())
		{
			UE_LOG(LogTemp, Display, TEXT("MovementComponent is now null"));
			MovementComp->SetComponentTickEnabled(false);
			MovementComp->SetUpdatedComponent(nullptr);
			MovementComp->Deactivate();
		}
	}

	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		UE_LOG(LogTemp, Display, TEXT("MeshComponent is now off"));
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		MeshComp->SetSimulatePhysics(false);

		MeshComp->SetCastShadow(bEnableShadowCasting);

		MeshComp->SetComponentTickEnabled(true);
		MeshComp->bTickInEditor = false;
	}
	
	Tags.AddUnique(TEXT("PortalReplica"));

	SetActorLabel(TEXT("PortalReplica"));
}

void AReplicaCharacter::SetReplicaVisibility(bool bVisible)
{
	bReplicaVisible = bVisible;
	SetActorHiddenInGame(!bVisible);
	UE_LOG(LogTemp, Display, TEXT("ReplicaVisibility : %d"), bVisible);
}



UAnimInstance* AReplicaCharacter::GetAnimInstance()
{
	return ReplicaAnimInstance;
}

void AReplicaCharacter::UpdateAnimationData(const FReplicaAnimationData& AnimData)
{
	AnimationData = AnimData;
	
	UpdateAnimInstanceProperties();
	OnAnimationDataUpdated(AnimData);
}

void AReplicaCharacter::TriggerPortalEffect(bool bEntering)
{
	//OnPortalEffectTriggered(bEntering);
	SetReplicaVisibility(bEntering);
}


void AReplicaCharacter::UpdateAnimInstanceProperties()
{
	
	if (!GetMesh()->GetAnimInstance() || !IsValid(GetMesh()->GetAnimInstance()))
	{
		return;
	}
	
	if (IsValid(ReplicaAnimInstance))
	{
		ReplicaAnimInstance->UpdateAnimationData(
			AnimationData.MovementSpeed,
			AnimationData.NormalizedSpeed,
			AnimationData.MovementDirection,
			AnimationData.bIsOnGround,
			AnimationData.bIsJumping,
			AnimationData.bIsFalling,
			AnimationData.VerticalSpeed,
			AnimationData.bHasWeapon,
			AnimationData.WeaponBobIntensity
		);
	}
}


void AReplicaCharacter::SetupReplicaDefaults()
{
	if (USkeletalMeshComponent* MeshComp = GetMesh())
	{
		
		MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		
		MeshComp->SetSimulatePhysics(false);
		
		MeshComp->SetCastShadow(bEnableShadowCasting);
		
		// update only bones
		MeshComp->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;

		if (UReplicaAnimInstance* TempAnimInstance = Cast<UReplicaAnimInstance>(GetMesh()->GetAnimInstance()))
		{
			ReplicaAnimInstance = TempAnimInstance;
		}
		
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

