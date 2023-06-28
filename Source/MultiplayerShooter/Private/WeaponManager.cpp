// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponManager.h"
#include "Weapons/WeaponBase.h"
#include "MainPlayerCharacter.h"

// Sets default values for this component's properties
UWeaponManager::UWeaponManager()
{
	// Turn off for now
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UWeaponManager::BeginPlay()
{
	Super::BeginPlay();

	AActor* OwnerActor = GetOwner();
	if (OwnerActor != nullptr) 
	{
		Character = Cast<AMainPlayerCharacter>(OwnerActor);
	}

	check(Character != nullptr);
}


// Called every frame
void UWeaponManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponManager::CreateWeapon(UClass* WeaponClass)
{
}

void UWeaponManager::SelectWeapon(AWeaponBase* Weapon)
{
}