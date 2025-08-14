// Fill out your copyright notice in the Description page of Project Settings.


#include "Park/ActorComponents/EquipmentComponent.h"
#include "Park/Player/PlayerCharacter.h"



// Sets default values for this component's properties
UEquipmentComponent::UEquipmentComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UEquipmentComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UEquipmentComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UEquipmentComponent::SetEquipment(AActor* NewEquipment)
{
	this->Equipment = NewEquipment;
	
	NewEquipment->AttachToActor(GetOwner(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, CastChecked<APlayerCharacter>(GetOwner())->EquipmentName);
	bEquipSomething = true;
}

void UEquipmentComponent::EquipmentAction()
{
	
}
