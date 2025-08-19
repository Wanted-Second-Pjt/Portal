// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Stuff/PortalInstancedStaticMeshActor.h"
#include "Components/InstancedStaticMeshComponent.h"

#include "Utility/Helper.h"


// Sets default values
APortalInstancedStaticMeshActor::APortalInstancedStaticMeshActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Helper::CreateSceneComponent<UInstancedStaticMeshComponent>(this, "MeshComp", GetRootComponent());
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComp->SetCollisionObjectType(ECC_WorldStatic);
	MeshComp->SetMobility(EComponentMobility::Static);
}

void APortalInstancedStaticMeshActor::DeActivateCollision()
{
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void APortalInstancedStaticMeshActor::ActivateCollision()
{
	MeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void APortalInstancedStaticMeshActor::DrawOwnArea()
{
}

// Called when the game starts or when spawned
void APortalInstancedStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
// void APortalInstancedStaticMeshActor::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
// }

