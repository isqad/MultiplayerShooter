// Fill out your copyright notice in the Description page of Project Settings.

#include "MainPlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "WeaponManager.h"
#include "HealthComponent.h"
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
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));
	
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

	FireStartEvent.BindUObject(this, &AMainPlayerCharacter::OnFireStart);
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
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::PlayerJump);
	PlayerInputComponent->BindAction("PrimaryAction", EInputEvent::IE_Pressed, this, &AMainPlayerCharacter::PrimaryAction);
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

void AMainPlayerCharacter::PlayerJump()
{
	Jump();
}

void AMainPlayerCharacter::PrimaryAction()
{
	FireStartEvent.ExecuteIfBound();
}

void AMainPlayerCharacter::OnFireStart_Implementation()
{
	if (GetWorld() == nullptr ||  GetWorld()->GetNetMode() == ENetMode::NM_Client) return;

	UE_LOG(LogTemp, Warning, TEXT("Fire!"));
}
