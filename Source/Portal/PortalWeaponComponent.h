// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "PortalWeaponComponent.generated.h"

class APortalCharacter;
class APlayerCharacter;

UCLASS(Blueprintable, BlueprintType, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PORTAL_API UPortalWeaponComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()

public:

	
	/** Projectile class to spawn */
	UPROPERTY(EditDefaultsOnly, Category=Projectile)
	TSubclassOf<class APortalProjectile> ProjectileClass;

	/** Sound to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;
	
	/** AnimMontage to play each time we fire */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* FireAnimation;

	/** Gun muzzle's offset from the characters location */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	FVector MuzzleOffset;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* FireMappingContext;

	/** Fire Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* FireAction;

	/** Sets default values for this component's properties */
	UPortalWeaponComponent();

	/** Attaches the actor to a FirstPersonCharacter */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	bool AttachWeapon(APortalCharacter* TargetCharacter);

	UFUNCTION(BlueprintCallable, Category="Weapon")
	bool AttachWeapon(APlayerCharacter* Player);

	/** Make the weapon Fire a Projectile */
	UFUNCTION(BlueprintCallable, Category="Weapon")
	void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PortalProjectile, meta = (AllowPrivateAccess = "true"))
	APortalProjectile* PortalProjectile1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PortalProjectile, meta = (AllowPrivateAccess = "true"))
	APortalProjectile* PortalProjectile2;


	bool CanFire = true;

protected:
	/** Ends gameplay for this component. */
	virtual void BeginPlay() override;

	UFUNCTION()
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	/** The Character holding this weapon*/
	APortalCharacter* Character;
	APlayerCharacter* PlayerPawn;
};
