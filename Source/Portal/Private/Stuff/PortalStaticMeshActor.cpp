// Fill out your copyright notice in the Description page of Project Settings.


#include "Stuff/PortalStaticMeshActor.h"

#include "Utility/Helper.h"


// Sets default values
APortalStaticMeshActor::APortalStaticMeshActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	this->GetStaticMeshComponent()->OnComponentHit.AddDynamic(this, &APortalStaticMeshActor::OnHit);
}

// Called when the game starts or when spawned
void APortalStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortalStaticMeshActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APortalStaticMeshActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
}

