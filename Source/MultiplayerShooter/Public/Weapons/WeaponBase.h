// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponBase.generated.h"

// Base class of Weapons
UCLASS()
class MULTIPLAYERSHOOTER_API AWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeaponBase();
	virtual void Tick(float DeltaTime) override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	void DisableCastShadow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	bool AbleToUse() const;

	virtual bool Use();
	
	void StopRateDelay();

	void FireStart();
	void FireStop();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USkeletalMeshComponent* Mesh{ nullptr };

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USceneComponent* DefaultScene{ nullptr };

	// Amount of cartriges in holder
	// TODO: in the base class?
	UPROPERTY(EditDefaultsOnly, Replicated, Category="Ammo")
	uint32 CurrentAmmo{ 20U };

	UPROPERTY(EditDefaultsOnly, Category="WeaponProperties")
	bool bAutoFire{ false };

	// Amount of pause between shoots in seconds
	UPROPERTY(EditDefaultsOnly, Category="WeaponProperties")
	float UseRateSeconds{ 1.f };

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float Damage{ 10.f };

private:
	UPROPERTY()
	bool bUseFreezedByRate{ false };

	UPROPERTY()
	bool bInFireState{ false };

	UPROPERTY()
	FTimerHandle UseWeaponTimerHandle{ FTimerHandle{} };
};
