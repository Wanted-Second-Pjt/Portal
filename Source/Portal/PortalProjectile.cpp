// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortalProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"

APortalProjectile::APortalProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &APortalProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	
	ProjectileMovement->ProjectileGravityScale = 0.0f; 
	ProjectileMovement->bSweepCollision = true;

	ProjectileMovement->bAutoActivate = false; // Don't move until launched


	// Die after 3 seconds by default
	
	InitialLifeSpan = 3.0f;


	
	PrimaryActorTick.bCanEverTick = false;


	
}



void APortalProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}

void APortalProjectile::BeginPlay()
{
	Super::BeginPlay();
	TSubclassOf<AActor> PortalClass = StaticLoadClass(AActor::StaticClass(), nullptr, TEXT("/Game/Kang/PortalSystem/BP_Portal.BP_Portal_C"));
	if (PortalClass)
	{
		TArray<AActor*> Portals;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), PortalClass, Portals);
		if (Portals.Num() > 0)
		{
			Portal = Portals[0];
		}
	
	
	}

	


}
