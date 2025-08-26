// Fill out your copyright notice in the Description page of Project Settings.


#include "Kang/PortalPortal.h"


// Sets default values
APortalPortal::APortalPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bIsActive = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent->Mobility = EComponentMobility::Static;

	PortalRootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("PortalRootComponent"));
	PortalRootComponent->SetupAttachment(GetRootComponent());
	PortalRootComponent->SetRelativeLocation( FVector(0.0f, 0.0f, 0.0f) );
	PortalRootComponent->SetRelativeRotation( FRotator(0.0f, 0.0f, 0.0f) );
	PortalRootComponent->Mobility = EComponentMobility::Movable;
}

bool APortalPortal::IsActive()
{
	return bIsActive;
}

void APortalPortal::SetActive( bool NewActive )
{
	bIsActive = NewActive;
}

void APortalPortal::ClearRTT_Implementation()
{

}

void APortalPortal::SetRTT_Implementation( UTexture* RenderTexture )
{

}

void APortalPortal::ForceTick_Implementation()
{

}

AActor* APortalPortal::GetTarget()
{
	return Target;
}

void APortalPortal::SetTarget(AActor* NewTarget)
{
	Target = NewTarget;
}

bool APortalPortal::IsPointInFrontOfPortal( FVector Point, FVector PortalLocation, FVector PortalNormal )
{
	FPlane PortalPlane  = FPlane( PortalLocation, PortalNormal );
	float PortalDot = PortalPlane.PlaneDot( Point );

	//If < 0 means we are behind the Plane
	return ( PortalDot >= 0 );
}

bool APortalPortal::IsPointCrossingPortal( FVector Point, FVector PortalLocation, FVector PortalNormal )
{
	FVector IntersectionPoint;
	FPlane PortalPlane  = FPlane( PortalLocation, PortalNormal );
	float PortalDot = PortalPlane.PlaneDot( Point );
	bool IsCrossing = false;
	bool IsInFront = PortalDot >= 0;

	bool IsIntersect = FMath::SegmentPlaneIntersection(  LastPosition,
															Point,
															PortalPlane,
															IntersectionPoint );

	// Did we intersect the portal since last Location ?
	// If yes, check the direction : crossing forward means we were in front and now at the back
	// If we crossed backward, ignore it
	if( IsIntersect && !IsInFront && LastInFront )
	{
		IsCrossing = true;
	}

	// Store values for next check
	LastInFront = IsInFront;
	LastPosition = Point;

	return IsCrossing;
}







// Called when the game starts or when spawned
void APortalPortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortalPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

