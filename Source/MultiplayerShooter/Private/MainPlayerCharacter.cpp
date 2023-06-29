// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WeaponManager.h"
#include "Weapons/RiffleBasic.h"

// Sets default values
AMainPlayerCharacter::AMainPlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetRootComponent());

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	Arms->SetupAttachment(Camera);

	WeaponManager = CreateDefaultSubobject<UWeaponManager>(TEXT("WeaponManager"));
	// AddOwnedComponent(WeaponManager);
	
	Arms->SetCastShadow(false);
	Arms->SetOnlyOwnerSee(true);

	GetMesh()->SetOwnerNoSee(true);
	
	GetCharacterMovement()->MaxWalkSpeed = 350.f;
	Camera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AMainPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void AMainPlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMainPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (PlayerInputComponent == nullptr) return;

	PlayerInputComponent->BindAxis("LookUpMouse", this, &AMainPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("TurnRightMouse", this, &AMainPlayerCharacter::TurnRight);

	PlayerInputComponent->BindAxis("MoveForward", this, &AMainPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainPlayerCharacter::MoveRight);
}

USkeletalMeshComponent* AMainPlayerCharacter::GetVisibleSkeletalMesh() const
{
	return IsLocallyControlled() ? Arms : GetMesh();
}

void AMainPlayerCharacter::LookUp(float AxisValue)
{
	AddControllerPitchInput(AxisValue);
}

void AMainPlayerCharacter::TurnRight(float AxisValue)
{
	AddControllerYawInput(AxisValue);
}

void AMainPlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector(), AxisValue);
}

void AMainPlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector(), AxisValue);
}
