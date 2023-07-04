// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/WeaponBase.h"
#include "FireWeapon.generated.h"

/**
 * 
 */
UCLASS()
class MULTIPLAYERSHOOTER_API AFireWeapon : public AWeaponBase
{
	GENERATED_BODY()

public:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
protected:
	UFUNCTION(Client, Reliable)
	void OnRep_Reloading();

	UFUNCTION(Server, Reliable)
	void Reload();

	bool Use() override;

	void GetFireTrace();

	UPROPERTY(EditDefaultsOnly, Replicated, Category="Ammo")
	uint32 TotalAmmo{ 100U };

	UPROPERTY(VisibleAnywhere, ReplicatedUsing=OnRep_Reloading, Category="Reloading")
	bool bReloading{ false };

	UPROPERTY(VisibleAnywhere, Category="Reloading")
	float ReloadTime{ 3.f };

	UPROPERTY(VisibleAnywhere, Category = "Reloading")
	uint32 AmmoToReload{ 0U };
};
