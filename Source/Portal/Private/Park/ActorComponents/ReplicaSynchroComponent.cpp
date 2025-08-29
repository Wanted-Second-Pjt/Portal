// Fill out your copyright notice in the Description page of Project Settings.

#include "Park/ActorComponents/ReplicaSynchroComponent.h"

#include "EngineUtils.h"
#include "Park/Player/PlayerCharacter.h"
#include "Park/ActorComponents/ControlComponent.h"
#include "Park/ActorComponents/EquipmentComponent.h"
#include "Park/RelatedPhysics/PlayerMovementComponent.h"
#include "Park/Player/ReplicaCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"
#include "Park/SceneComponents/PortalComponent.h"

UReplicaSynchroComponent::UReplicaSynchroComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	bSyncMovementState = false; // When Use Anim Inst
	// Runtime Synchro Status
	LastSyncTime = 0.0f;
	// Synchro Status
	SyncFrequency = 30.0f;
	
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
	
	// When Use AnimInstance
	if (bSyncMovementState)
	{
		// 30 FPS hard Coding. need to modify
		if (const float CurrentTime = GetWorld()->GetTimeSeconds();
			CurrentTime - LastSyncTime > (1.0f / SyncFrequency))
		{
			LastSyncTime = CurrentTime;
		}
	}
}

void UReplicaSynchroComponent::CreateReplica()
{
	if (!GetWorld() || !IsValid(GetOwner()))
	{
		return;
	}
	
	if (CurrentReplica && IsValid(CurrentReplica))
	{
		DestroyReplica();
	}
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	SpawnParams.Owner = GetOwner();
	SpawnParams.TransformScaleMethod = ESpawnActorScaleMethod::OverrideRootScale;
	SpawnParams.CustomPreSpawnInitalization =
		[&](AActor* SpawnedActor)
		{
			SpawnedActor->DisableInput(nullptr);
			if (USkeletalMeshComponent* ReplicaSKM = SpawnedActor->FindComponentByClass<USkeletalMeshComponent>())
			{
				UE_LOG(LogTemp, Display, TEXT("Replica SKM Exist"));
				ReplicaSKM->SetSkeletalMesh(GetPlayerCharacter()->GetSkeletalComp()->GetSkeletalMeshAsset());
				ReplicaSKM->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				ReplicaSKM->SetSimulatePhysics(false);
				ReplicaSKM->SetCastShadow(true);
			}
			
		};
	
	FTransform SpawnTransform = GetOwner()->GetActorTransform();
	SpawnTransform.SetTranslation(SpawnTransform.GetTranslation() + ReplicaSpawnOffset);
	CurrentReplica = GetWorld()->SpawnActor<AReplicaCharacter>(AReplicaCharacter::StaticClass(), SpawnTransform, SpawnParams);
	
	if (IsValid(CurrentReplica))
	{
		UE_LOG(LogTemp, Display, TEXT("Replica Character Synced In ReplicaSync Component"));
		//FOnAttachPortal OnAttachPortal;
		//FOnDetachPortal OnDetachPortal;
		
		FOnAttachPortal().AddUniqueDynamic(this, &UReplicaSynchroComponent::OnReplicaVisible);
		FOnDetachPortal().AddUniqueDynamic(this, &UReplicaSynchroComponent::OnReplicaInvisible);
		SetupPortalCamera();
	}
}

void UReplicaSynchroComponent::DestroyReplica()
{
	if (CurrentReplica && IsValid(CurrentReplica))
	{
		FOnDetachPortal().Broadcast();
		
		FOnAttachPortal().RemoveDynamic(this, &UReplicaSynchroComponent::OnReplicaVisible);
		FOnDetachPortal().RemoveDynamic(this, &UReplicaSynchroComponent::OnReplicaInvisible);
		
		CurrentReplica->Destroy();
		CurrentReplica = nullptr;
	}
}

void UReplicaSynchroComponent::SyncToReplica(const bool& bLink)
{
	if (!CurrentReplica || !IsValid(CurrentReplica))
	{
		return;
	}
	
	if (bSyncMovementState)
	{
		UE_LOG(LogTemp, Display, TEXT("Replica Synchronization State : Anim Inst"));
		SyncMovementData(); // Update data, Replica will pull when Needed
		return;
	}
	
	UE_LOG(LogTemp, Display, TEXT("Replica Synchronization State : Pose"));
	SyncToReplicaPose(bLink);
}

void UReplicaSynchroComponent::SyncToReplicaPose(const bool& bLink)
{
	if (IsValid(GetPlayerCharacter()))
	{
		if (USkeletalMeshComponent* ReplicaMeshComp = CurrentReplica->GetMesh();
			IsValid(ReplicaMeshComp) && IsValid(GetPlayerCharacter()->GetSkeletalComp())
		)
		{
			bLink ?
				ReplicaMeshComp->SetLeaderPoseComponent(GetPlayerCharacter()->GetSkeletalComp(), false, true)
				: ReplicaMeshComp->SetLeaderPoseComponent(nullptr, false, false);
		}
	}
	
}

void UReplicaSynchroComponent::OnReplicaVisible()
{
	if (IsValid(CurrentReplica))
	{
		//CurrentReplica->TriggerPortalEffect(true);  // AnimInstance
		CurrentReplica->SetReplicaVisibility(true);
		SyncToReplica(true);
	}
	
}

void UReplicaSynchroComponent::OnReplicaInvisible()
{
	if (IsValid(CurrentReplica))
	{
		//CurrentReplica->TriggerPortalEffect(false);  // AnimInstance
		CurrentReplica->SetReplicaVisibility(false);
		SyncToReplica(false);
	}
}


void UReplicaSynchroComponent::SetupPortalCamera()
{
	if (!CurrentReplica || !IsValid(CurrentReplica))
	{
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("Enter Portal Camera Setup"));
	TArray<AActor*> Portals;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Portal"), Portals);
	for (AActor* Portal : Portals)
	{
		if (USceneCaptureComponent2D* SceneCapture = Portal->FindComponentByClass<USceneCaptureComponent2D>())
		{
			UE_LOG(LogTemp, Display, TEXT("Find Success Portal Camera"));
			//SceneCapture->HiddenActors.Empty();
			SceneCapture->HiddenActors.AddUnique(CurrentReplica);
			
			// Replica wouldn't be Rendered by Portal Cam
			//PortalCamera->bCaptureEveryFrame = true;
			//PortalCamera->bCaptureOnMovement = true;
		}
	}
	//SetReplicaVisibility(true);
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
	
	if (IsValid(CurrentReplica->GetAnimInstance()))
	{
		CurrentReplica->UpdateAnimationData(AnimData);
	}
}

APlayerCharacter* UReplicaSynchroComponent::GetPlayerCharacter() const
{
	return Cast<APlayerCharacter>(GetOwner());
}


