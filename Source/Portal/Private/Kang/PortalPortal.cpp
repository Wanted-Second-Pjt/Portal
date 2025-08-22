// Fill out your copyright notice in the Description page of Project Settings.


#include "Kang/PortalPortal.h"

// Sets default values
APortalPortal::APortalPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

