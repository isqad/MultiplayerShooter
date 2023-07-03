// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MULTIPLAYERSHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHealthComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const;

	// only server
	UFUNCTION()
	void ApplyDamage(float Damage);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	ACharacter* Character;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	float Health;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	float Armor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated)
	bool bDead;
};
