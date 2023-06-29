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

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USceneComponent* DefaultScene;
};
