// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Stuff/PortalStaticMeshActor.h"

#include "PortalProjectile.h"


// Sets default values
APortalStaticMeshActor::APortalStaticMeshActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void APortalStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void APortalStaticMeshActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(APortalProjectile::StaticClass()) == bPortal)
	{
		// Portal 생성 로직	
	}
	return;
}


