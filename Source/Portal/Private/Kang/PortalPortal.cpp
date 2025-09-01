// Fill out your copyright notice in the Description page of Project Settings.


#include "Kang/PortalPortal.h"

#include "Components/BoxComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "Kismet/GameplayStatics.h"
#include "Park/Stuff/PortalPlatform.h"
//#include "Utility/DebugHelper.h"


// Sets default values
APortalPortal::APortalPortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);
	
	PortalCamera = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("PortalCamera"));
	PortalCamera->SetupAttachment(SceneRoot);



}


// Called when the game starts or when spawned
void APortalPortal::BeginPlay()
{
	Super::BeginPlay();

	GetComponentByClass<UBoxComponent>()->OnComponentBeginOverlap.AddDynamic(this, &APortalPortal::OnPortalNoticeObject);
	GetComponentByClass<UBoxComponent>()->OnComponentEndOverlap.AddDynamic(this, &APortalPortal::OnPortalUnNoticeObject);
	
}

// Called every frame
void APortalPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortalPortal::OnPortalNoticeObject(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//UE_LOG(CustomDebuggingLog, Warning, TEXT("OtherActor : %s"), *OtherActor->GetClass()->GetName());
	
	if (OtherActor->GetClass() == GetWorld()->GetFirstPlayerController()->GetPawn()->GetClass())
	{
		//UE_LOG(CustomDebuggingLog, Warning, TEXT("Player : %s"), *GetWorld()->GetFirstPlayerController()->GetPawn()->GetClass()->GetName());
		OnAttachPortal.Broadcast(this);
	}
}

void APortalPortal::OnPortalUnNoticeObject(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (Cast<APlayerCharacter>(OtherActor))
	{
		OnDetachPortal.Broadcast(this);
	}
}

void APortalPortal::SetClipPlane_Implementation()
{
}


