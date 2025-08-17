// Fill out your copyright notice in the Description page of Project Settings.

#include "Park/ActorComponents/ReplicaSynchroComponent.h"
#include "Park/Player/PlayerCharacter.h"
#include "Park/ActorComponents/ControlComponent.h"
#include "Park/ActorComponents/EquipmentComponent.h"
#include "Park/RelatedPhysics/PlayerMovementComponent.h"
#include "Park/Player/ReplicaCharacter.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimInstance.h"
#include "Kismet/KismetMathLibrary.h"

UReplicaSynchroComponent::UReplicaSynchroComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	// Runtime Synchro Status
	LastSyncTime = 0.0f;
	bReplicaVisible = true;
	CurrentFadeAlpha = 1.0f;
	
	// Synchro Status
	SyncFrequency = 30.0f;
	bSyncBoneTransforms = true;
	bSyncMovementState = true;
	bSyncEquipmentState = true;
}

void UReplicaSynchroComponent::BeginPlay()
{
	Super::BeginPlay();

	// Comp Var for Using Usually
	if (APlayerCharacter* Player = GetPlayerCharacter())
	{
		CachedMovementComp = Player->FindComponentByClass<UPlayerMovementComponent>();
		CachedControlComp = Player->FindComponentByClass<UControlComponent>();
		CachedEquipmentComp = Player->FindComponentByClass<UEquipmentComponent>();
	}
	
	// Debuging
	if (ReplicaClass)
	{
		CreateReplica();
	}
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
	
	// Fade. delete this
	if (!bReplicaVisible && CurrentFadeAlpha > 0.0f)
	{
		CurrentFadeAlpha = FMath::FInterpTo(CurrentFadeAlpha, 0.0f, DeltaTime, PortalFadeSpeed);
		
		if (USkeletalMeshComponent* ReplicaMesh = CurrentReplica->GetMesh())
		{
			// ReplicaMesh->SetScalarParameterValueOnMaterials(TEXT("Opacity"), CurrentFadeAlpha);
		}
		
		if (CurrentFadeAlpha <= 0.01f)
		{
			CurrentReplica->SetActorHiddenInGame(true);
		}
	}
	else if (bReplicaVisible && CurrentFadeAlpha < 1.0f)
	{
		CurrentReplica->SetActorHiddenInGame(false);
		CurrentFadeAlpha = FMath::FInterpTo(CurrentFadeAlpha, 1.0f, DeltaTime, PortalFadeSpeed);
		
		if (USkeletalMeshComponent* ReplicaMesh = CurrentReplica->GetMesh())
		{
			// ReplicaMesh->SetScalarParameterValueOnMaterials(TEXT("Opacity"), CurrentFadeAlpha);
		}
	}
}

void UReplicaSynchroComponent::CreateReplica()
{
	if (!ReplicaClass || !GetWorld())
	{
		return;
	}
	
	if (CurrentReplica && IsValid(CurrentReplica))
	{
		DestroyReplica();
	}
	
	APlayerCharacter* Player = GetPlayerCharacter();
	if (!Player)
	{
		return;
	}
	
	FVector SpawnLocation = Player->GetActorLocation() + ReplicaSpawnOffset;
	FRotator SpawnRotation = Player->GetActorRotation();
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	
	CurrentReplica = GetWorld()->SpawnActor<ACharacter>(ReplicaClass, SpawnLocation, SpawnRotation, SpawnParams);
	
	if (CurrentReplica)
	{
		CurrentReplica->DisableInput(nullptr);
		
		if (USkeletalMeshComponent* ReplicaMesh = CurrentReplica->GetMesh())
		{
			ReplicaMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			ReplicaMesh->SetSimulatePhysics(false);
			// Player can see
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
		
		bReplicaVisible = true;
		CurrentFadeAlpha = 1.0f;
	}
}

void UReplicaSynchroComponent::SyncToReplica()
{
	if (!CurrentReplica || !IsValid(CurrentReplica))
	{
		return;
	}
	
	if (bSyncBoneTransforms)
	{
		SyncBoneTransforms();
	}
	
	if (bSyncMovementState)
	{
		SyncMovementData();
	}
	
	if (bSyncEquipmentState)
	{
		SyncEquipmentState();
	}
	
	SyncPortalWeaponAnimation();
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
	if (AReplicaCharacter* ReplicaChar = Cast<AReplicaCharacter>(CurrentReplica))
	{
		ReplicaChar->TriggerPortalEffect(false);
	}
	
	SyncToReplica();
}

void UReplicaSynchroComponent::UpdateReplicaVisibility(bool bVisible)
{
	bReplicaVisible = bVisible;
}

void UReplicaSynchroComponent::SyncBoneTransforms()
{
	if (!CurrentReplica || !CachedMovementComp)
	{
		return;
	}
	
	APlayerCharacter* Player = GetPlayerCharacter();
	if (!Player)
	{
		return;
	}
	
	USkeletalMeshComponent* PlayerMesh = Player->GetSkeletalComp();
	USkeletalMeshComponent* ReplicaMesh = CurrentReplica->GetMesh();
	
	if (!PlayerMesh || !ReplicaMesh)
	{
		return;
	}
	
	for (const FName& BoneName : ImportantBones)
	{
		int32 PlayerBoneIndex = PlayerMesh->GetBoneIndex(BoneName);
		int32 ReplicaBoneIndex = ReplicaMesh->GetBoneIndex(BoneName);
		
		if (PlayerBoneIndex != INDEX_NONE && ReplicaBoneIndex != INDEX_NONE)
		{
			FTransform BoneTransform = PlayerMesh->GetBoneTransform(PlayerBoneIndex);

			// 새로 함수 만들어야함
			//ReplicaMesh->SetBoneTransformByName(BoneName, BoneTransform, EBoneSpaces::ComponentSpace);
		}
	}
}

void UReplicaSynchroComponent::SyncAnimationState()
{
}

void UReplicaSynchroComponent::SyncMovementData()
{
	if (!CurrentReplica || !CachedMovementComp || !CachedControlComp)
	{
		return;
	}
	
	FVector Velocity = CachedMovementComp->GetCurrentVelocity();
	float MovementSpeed = Velocity.Size();
	FVector2D MovementDirection = CachedControlComp->GetDirection();
	bool bIsOnGround = CachedMovementComp->IsOnGround();
	
	if (AReplicaCharacter* ReplicaChar = Cast<AReplicaCharacter>(CurrentReplica))
	{
		
		ReplicaChar->UpdateMovementData(MovementSpeed, MovementDirection, bIsOnGround);
	}
	else
	{
		USkeletalMeshComponent* ReplicaMesh = CurrentReplica->GetMesh();
		if (!ReplicaMesh)
		{
			return;
		}
		
		UAnimInstance* AnimInstance = ReplicaMesh->GetAnimInstance();
		if (!AnimInstance)
		{
			return;
		}
		
		SetAnimInstanceProperty(TEXT("MovementSpeed"), MovementSpeed);
		
		float NormalizedSpeed = FMath::Clamp(MovementSpeed / CachedMovementComp->MaxWalkSpeed, 0.0f, 1.0f);
		SetAnimInstanceProperty(TEXT("NormalizedSpeed"), NormalizedSpeed);
		
		SetAnimInstanceProperty(TEXT("MovementDirection"), MovementDirection);
		SetAnimInstanceProperty(TEXT("bIsOnGround"), bIsOnGround);
		
		bool bIsJumping = !bIsOnGround && Velocity.Z > 0;
		bool bIsFalling = !bIsOnGround && Velocity.Z < 0;
		SetAnimInstanceProperty(TEXT("bIsJumping"), bIsJumping);
		SetAnimInstanceProperty(TEXT("bIsFalling"), bIsFalling);
		SetAnimInstanceProperty(TEXT("VerticalSpeed"), static_cast<float>(Velocity.Z));
	}
}

void UReplicaSynchroComponent::SyncEquipmentState()
{
	if (!CurrentReplica || !CachedEquipmentComp)
	{
		return;
	}
	
	bool bHasEquipment = CachedEquipmentComp->bEquipSomething;
	int32 WeaponType = 1; // Portal Gun = 1
	
	if (AReplicaCharacter* ReplicaChar = Cast<AReplicaCharacter>(CurrentReplica))
	{
		ReplicaChar->UpdateEquipmentState(bHasEquipment, WeaponType);
	}
	else
	{
		USkeletalMeshComponent* ReplicaMesh = CurrentReplica->GetMesh();
		if (!ReplicaMesh)
		{
			return;
		}
		
		UAnimInstance* AnimInstance = ReplicaMesh->GetAnimInstance();
		if (!AnimInstance)
		{
			return;
		}
		
		SetAnimInstanceProperty(TEXT("bHasWeapon"), bHasEquipment);
		SetAnimInstanceProperty(TEXT("WeaponType"), static_cast<float>(WeaponType));
	}
}

void UReplicaSynchroComponent::SyncPortalWeaponAnimation()
{
	if (!CurrentReplica || !CachedMovementComp)
	{
		return;
	}
	
	UAnimInstance* AnimInstance = CurrentReplica->GetMesh()->GetAnimInstance();
	if (!AnimInstance)
	{
		return;
	}
	
	// portal gun impulse
	float MovementSpeed = CachedMovementComp->GetCurrentVelocity().Size();
	float WeaponBobIntensity = FMath::Clamp(MovementSpeed / CachedMovementComp->MaxWalkSpeed, 0.0f, 1.0f);
	SetAnimInstanceProperty(TEXT("WeaponBobIntensity"), WeaponBobIntensity);
	
	// Portal gun fire motion?
	// SetAnimInstanceProperty(TEXT("bFiringPortal"), bFiringPortal);
}

APlayerCharacter* UReplicaSynchroComponent::GetPlayerCharacter() const
{
	return Cast<APlayerCharacter>(GetOwner());
}

void UReplicaSynchroComponent::SetAnimInstanceProperty(const FString& PropertyName, float Value)
{
	if (!CurrentReplica)
	{
		return;
	}
	
	USkeletalMeshComponent* ReplicaMesh = CurrentReplica->GetMesh();
	if (!ReplicaMesh)
	{
		return;
	}
	
	UAnimInstance* AnimInstance = ReplicaMesh->GetAnimInstance();
	if (!AnimInstance)
	{
		return;
	}
	
	if (FProperty* Property = AnimInstance->GetClass()->FindPropertyByName(*PropertyName))
	{
		if (FFloatProperty* FloatProp = CastField<FFloatProperty>(Property))
		{
			FloatProp->SetPropertyValue_InContainer(AnimInstance, Value);
		}
	}
}

void UReplicaSynchroComponent::SetAnimInstanceProperty(const FString& PropertyName, bool Value)
{
	if (!CurrentReplica)
	{
		return;
	}
	
	USkeletalMeshComponent* ReplicaMesh = CurrentReplica->GetMesh();
	if (!ReplicaMesh)
	{
		return;
	}
	
	UAnimInstance* AnimInstance = ReplicaMesh->GetAnimInstance();
	if (!AnimInstance)
	{
		return;
	}
	
	if (FProperty* Property = AnimInstance->GetClass()->FindPropertyByName(*PropertyName))
	{
		if (FBoolProperty* BoolProp = CastField<FBoolProperty>(Property))
		{
			BoolProp->SetPropertyValue_InContainer(AnimInstance, Value);
		}
	}
}

void UReplicaSynchroComponent::SetAnimInstanceProperty(const FString& PropertyName, const FVector2D& Value)
{
	if (!CurrentReplica)
	{
		return;
	}
	
	USkeletalMeshComponent* ReplicaMesh = CurrentReplica->GetMesh();
	UAnimInstance* AnimInstance = ReplicaMesh->GetAnimInstance();
	if (!IsValid(ReplicaMesh) || !IsValid(AnimInstance))
	{
		return;
	}
	
	if (FProperty* Property = AnimInstance->GetClass()->FindPropertyByName(*PropertyName))
	{
		if (FStructProperty* StructProp = CastField<FStructProperty>(Property))
		{
			if (StructProp->Struct == TBaseStructure<FVector2D>::Get())
			{
				//StructProp->SetPropertyValue_InContainer(AnimInstance, &Value);
			}
		}
	}
}

