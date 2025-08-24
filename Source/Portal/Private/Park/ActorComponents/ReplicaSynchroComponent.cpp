// Fill out your copyright notice in the Description page of Project Settings.

#include "Park/ActorComponents/ReplicaSynchroComponent.h"
#include "Park/Player/PlayerCharacter.h"
#include "Park/ActorComponents/ControlComponent.h"
#include "Park/ActorComponents/EquipmentComponent.h"
#include "Park/RelatedPhysics/PlayerMovementComponent.h"
#include "Park/Player/ReplicaCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"

UReplicaSynchroComponent::UReplicaSynchroComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Runtime Synchro Status
	LastSyncTime = 0.0f;
	
	// Synchro Status
	SyncFrequency = 30.0f;
	bSyncMovementState = true;
}

void UReplicaSynchroComponent::BeginPlay()
{
	Super::BeginPlay();

	// Comp Var for Using Usually
	if (IsValid(GetOwner()))
	{
		MovementComp = GetOwner()->FindComponentByClass<UPlayerMovementComponent>();
		ControlComp = GetOwner()->FindComponentByClass<UControlComponent>();
		EquipmentComp = GetOwner()->FindComponentByClass<UEquipmentComponent>();
	}
	
	CreateReplica();
}

void UReplicaSynchroComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!CurrentReplica || !IsValid(CurrentReplica))
	{
		return;
	}
	
	// 30 FPS hard Coding. need to modify
	if (float CurrentTime = GetWorld()->GetTimeSeconds(); CurrentTime - LastSyncTime > (1.0f / SyncFrequency))
	{
		SyncToReplica();
		LastSyncTime = CurrentTime;
	}
}

void UReplicaSynchroComponent::CreateReplica()
{
	if (!GetWorld())
	{
		return;
	}
	
	if (CurrentReplica && IsValid(CurrentReplica))
	{
		DestroyReplica();
	}
	
	if (!IsValid(GetOwner()))
	{
		return;
	}
	
	FVector SpawnLocation = GetOwner()->GetActorLocation() + ReplicaSpawnOffset;
	FRotator SpawnRotation = GetOwner()->GetActorRotation();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	CurrentReplica = GetWorld()->SpawnActor<AReplicaCharacter>(SpawnLocation, SpawnRotation, SpawnParams);
	
	if (CurrentReplica)
	{
		CurrentReplica->DisableInput(nullptr);
		
		if (USkeletalMeshComponent* ReplicaMesh = CurrentReplica->GetMesh())
		{
			ReplicaMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			ReplicaMesh->SetSimulatePhysics(false);
			ReplicaMesh->SetCastShadow(true);
		}
		
		SyncToReplica();
		
		OnReplicaCreated.Broadcast(CurrentReplica);
	}
}

void UReplicaSynchroComponent::DestroyReplica()
{
	if (CurrentReplica && IsValid(CurrentReplica))
	{
		OnReplicaDestroyed.Broadcast(CurrentReplica);
		
		CurrentReplica->Destroy();
		CurrentReplica = nullptr;
	}
}

void UReplicaSynchroComponent::SyncToReplica()
{
	if (bSyncMovementState)
	{
		SyncMovementData(); // Update data, Replica will pull when Needed
	}
}

void UReplicaSynchroComponent::OnPlayerEnterPortal()
{
	if (AReplicaCharacter* ReplicaChar = Cast<AReplicaCharacter>(CurrentReplica))
	{
		ReplicaChar->TriggerPortalEffect(true);
	}
	
}

void UReplicaSynchroComponent::OnPlayerExitPortal()
{
	if (IsValid(CurrentReplica))
	{
		CurrentReplica->TriggerPortalEffect(false);
	}
	
	SyncToReplica();
}

void UReplicaSynchroComponent::SetReplicaVisibility(bool bVisible)
{
	if (CurrentReplica && IsValid(CurrentReplica))
	{
		CurrentReplica->SetReplicaVisibility(bVisible);
	}
}

void UReplicaSynchroComponent::SetupPortalCamera(USceneCaptureComponent2D* PortalCamera)
{
	if (!PortalCamera || !CurrentReplica || !IsValid(CurrentReplica))
	{
		return;
	}
	
	
	// Replica Can't be Rendered by Portal Cam
	if (APlayerCharacter* Player = GetPlayerCharacter())
	{
		PortalCamera->HiddenActors.AddUnique(GetCurrentReplica());
	}
	//PortalCamera->bCaptureEveryFrame = true;
	//PortalCamera->bCaptureOnMovement = true;
	
	//SetReplicaVisibility(true);
	SyncToReplica();
}


void UReplicaSynchroComponent::SyncMovementData()
{
	if (!CurrentReplica || !IsValid(CurrentReplica) || !MovementComp || !ControlComp)
	{
		return;
	}
	
	FReplicaAnimationData AnimData;
	
	FVector Velocity = MovementComp->GetCurrentVelocity();
	AnimData.MovementSpeed = Velocity.Size();
	AnimData.NormalizedSpeed = FMath::Clamp(AnimData.MovementSpeed / MovementComp->MaxWalkSpeed, 0.0f, 1.0f);
	AnimData.MovementDirection = ControlComp->GetDirection();
	AnimData.bIsOnGround = MovementComp->IsOnGround();
	AnimData.VerticalSpeed = Velocity.Z;
	
	AnimData.bIsJumping = !AnimData.bIsOnGround && Velocity.Z > 0;
	AnimData.bIsFalling = !AnimData.bIsOnGround && Velocity.Z < 0;
	
	if (EquipmentComp)
	{
		AnimData.bHasWeapon = EquipmentComp->bEquipSomething;
	}
	
	AnimData.WeaponBobIntensity = FMath::Clamp(AnimData.MovementSpeed / MovementComp->MaxWalkSpeed, 0.0f, 1.0f);
	
	if (AReplicaCharacter* ReplicaChar = Cast<AReplicaCharacter>(CurrentReplica))
	{
		ReplicaChar->UpdateAnimationData(AnimData);
	}
}

APlayerCharacter* UReplicaSynchroComponent::GetPlayerCharacter() const
{
	return Cast<APlayerCharacter>(GetOwner());
}


