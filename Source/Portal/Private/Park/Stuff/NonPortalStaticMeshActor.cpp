// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Stuff/NonPortalStaticMeshActor.h"

#include "PortalProjectile.h"


// Sets default values
ANonPortalStaticMeshActor::ANonPortalStaticMeshActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bPortal = false;
}

// Called when the game starts or when spawned
void ANonPortalStaticMeshActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ANonPortalStaticMeshActor::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(APortalProjectile::StaticClass()) == bPortal)
	{
		// 픽하고 사라지는 이펙트 연출
	}
	return;
}
