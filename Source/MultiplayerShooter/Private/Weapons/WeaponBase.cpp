// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/WeaponBase.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"
#include "GenericPlatform/GenericPlatformMath.h"

// Sets default values
AWeaponBase::AWeaponBase()
{
 	// Disabled for now
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	DefaultScene = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneComponent"));
	SetRootComponent(DefaultScene);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	Mesh->SetupAttachment(DefaultScene);
}

void AWeaponBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(AWeaponBase, CurrentAmmo, COND_OwnerOnly);
}

// Called when the game starts or when spawned
void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::DisableCastShadow()
{
	if (Mesh == nullptr) return;

	Mesh->SetCastShadow(false);
}

void AWeaponBase::FireStart()
{
	bInFireState = true;
}

void AWeaponBase::FireStop()
{
	bInFireState = false;
}

inline bool AWeaponBase::AbleToUse() const
{
	return CurrentAmmo > 0 && !bUseFreezedByRate;
}

bool AWeaponBase::Use()
{
	UE_LOG(LogTemp, Warning, TEXT("Use called from WeaponBase class"));

	if (!AWeaponBase::AbleToUse()) return false;

	CurrentAmmo = FGenericPlatformMath::Min<uint32>(CurrentAmmo - 1, 0U);

	GetWorldTimerManager().SetTimer(UseWeaponTimerHandle, this, &AWeaponBase::StopRateDelay, UseRateSeconds, false);

	bUseFreezedByRate = true;

	return true;
}

void AWeaponBase::StopRateDelay()
{
	bUseFreezedByRate = false;

	if (bAutoFire && bInFireState)
	{
		Use();
	}
}