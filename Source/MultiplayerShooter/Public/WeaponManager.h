// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponManager.generated.h"

class AWeaponBase;
class AMainPlayerCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYERSHOOTER_API UWeaponManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UWeaponManager();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	AWeaponBase* CreateWeapon(UClass* WeaponClass);

	UFUNCTION(BlueprintAuthorityOnly, BlueprintCallable)
	void SelectWeapon(AWeaponBase* Weapon);

	UFUNCTION()
	void OnRep_SetCurrentWeapon();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleInstanceOnly, ReplicatedUsing=OnRep_SetCurrentWeapon, Category = "Weapons")
	AWeaponBase* CurrentWeapon;

	UPROPERTY(VisibleInstanceOnly, replicated, Category = "Weapons")
	AWeaponBase* MainWeapon;

	UPROPERTY(VisibleInstanceOnly, replicated, Category = "Weapons")
	AWeaponBase* SecondaryWeapon;

	UPROPERTY(VisibleInstanceOnly, replicated, Category = "Weapons")
	AWeaponBase* MeleeWeapon;

	UPROPERTY(VisibleInstanceOnly, replicated, Category = "Weapons")
	TArray<AWeaponBase*> Grenades;

	UPROPERTY(VisibleInstanceOnly, replicated)
	AMainPlayerCharacter* Character;

private:
	void AttachCurrentWeaponToCharacter();
	void DisableShadow();
};
