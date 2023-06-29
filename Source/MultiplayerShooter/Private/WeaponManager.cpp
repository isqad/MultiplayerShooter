// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponManager.h"
#include "Weapons/WeaponBase.h"
#include "MainPlayerCharacter.h"
#include "Net/UnrealNetwork.h"
#include "Engine/ActorChannel.h"

// Sets default values for this component's properties
UWeaponManager::UWeaponManager()
{
	// Turn off for now
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
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

	if (GEngine && !GetWorld()->IsServer())
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("WeaponManager BeginPlay!"));
	}
}


// Called every frame
void UWeaponManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeaponManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UWeaponManager, Character);
	DOREPLIFETIME(UWeaponManager, MainWeapon);
	DOREPLIFETIME(UWeaponManager, SecondaryWeapon);
	DOREPLIFETIME(UWeaponManager, MeleeWeapon);
	DOREPLIFETIME(UWeaponManager, Grenades);
	DOREPLIFETIME(UWeaponManager, CurrentWeapon);
}

AWeaponBase* UWeaponManager::CreateWeapon(UClass* WeaponClass)
{
	if (!GetWorld()->IsServer()) return nullptr;

	AActor* SpawnedWeapon = GetWorld()->SpawnActor(WeaponClass);
	check(SpawnedWeapon != nullptr);

	AWeaponBase* Weapon = Cast<AWeaponBase>(SpawnedWeapon);
	check(Weapon != nullptr);

	return Weapon;
}

void UWeaponManager::SelectWeapon(AWeaponBase* Weapon)
{
	if (!GetWorld()->IsServer()) return;

	check(Weapon != nullptr);
	CurrentWeapon = Weapon;
}

// Called on Clients
void UWeaponManager::OnRep_SetCurrentWeapon()
{
	if (GetWorld()->IsServer() && CurrentWeapon == nullptr) return;

	USkeletalMeshComponent* ParentMesh = Character->GetVisibleSkeletalMesh();
	FAttachmentTransformRules AttachmentRules{
		EAttachmentRule::KeepRelative, // Location Rule
		EAttachmentRule::KeepRelative, // Rotation Rule
		EAttachmentRule::KeepRelative, // Scale Rule
		true
	};
	CurrentWeapon->AttachToComponent(ParentMesh, AttachmentRules, FName("GripPoint"));
}

