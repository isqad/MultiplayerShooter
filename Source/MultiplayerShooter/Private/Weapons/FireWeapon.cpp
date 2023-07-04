// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/FireWeapon.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

void AFireWeapon::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AFireWeapon, TotalAmmo, COND_OwnerOnly);
}

void AFireWeapon::OnRep_Reloading_Implementation()
{
}

void AFireWeapon::Reload_Implementation()
{
	if (bReloading) return;

	bReloading = true;
}

bool AFireWeapon::Use()
{
	bool used = Super::Use();

	UE_LOG(LogTemp, Warning, TEXT("Use called from AFireWeapon class"));

	if (used)
	{
		UE_LOG(LogTemp, Warning, TEXT("CurrentAmmo: %d, TotalAmmo: %d"), CurrentAmmo, TotalAmmo);

		GetFireTrace();
	}

	return used;
}

void AFireWeapon::GetFireTrace()
{
}
