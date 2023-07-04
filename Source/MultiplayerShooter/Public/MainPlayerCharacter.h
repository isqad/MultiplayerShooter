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

	DECLARE_DELEGATE(FFireStartEvent)
	FFireStartEvent FireStartEvent {};
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void OnFireStart();
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UCameraComponent* Camera{ nullptr };

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	USkeletalMeshComponent* Arms{ nullptr };

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UWeaponManager* WeaponManager{ nullptr };

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	UHealthComponent* HealthComponent{ nullptr };

private:
	void LookUp(float AxisValue);
	void TurnRight(float AxisValue);
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PlayerJump();
	void PrimaryAction();
};
