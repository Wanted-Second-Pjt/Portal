// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/Maps/TestLevel.h"


// Sets default values
ATestLevel::ATestLevel()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ATestLevel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATestLevel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

