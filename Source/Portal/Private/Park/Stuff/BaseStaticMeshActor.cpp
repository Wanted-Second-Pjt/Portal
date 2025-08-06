// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Stuff/BaseStaticMeshActor.h"

#include "Utility/Helper.h"


// Sets default values
ABaseStaticMeshActor::ABaseStaticMeshActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorTickEnabled(false);
	
	this->GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &ABaseStaticMeshActor::OnHit);
}

// Called when the game starts or when spawned
void ABaseStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseStaticMeshActor::SetActorTickEnabled(const bool bEnabled)
{
	Super::SetActorTickEnabled(bEnabled);
}