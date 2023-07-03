// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MainPlayerCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class UWeaponManager;
class UHealthComponent;

UCLASS()
class MULTIPLAYERSHOOTER_API AMainPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainPlayerCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintPure)
	USkeletalMeshComponent* GetVisibleSkeletalMesh() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USkeletalMeshComponent* Arms;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UWeaponManager* WeaponManager;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UHealthComponent* HealthComponent;

private:
	void LookUp(float AxisValue);
	void TurnRight(float AxisValue);
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PlayerJump();
};
