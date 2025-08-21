// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Item.h"
#include "Items/Weapons/weapon.h"


ASlashCharacter::ASlashCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;

	ViewCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	ViewCamera->SetupAttachment(CameraBoom);
}


void ASlashCharacter::MoveForward(float Value)
{
	if(Controller &&(Value != 0.0f))
	{
		// find out which way is forward
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0, ControlRotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);

	}
}
void ASlashCharacter::MoveRight(float Value)
{
	if(Controller && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator ControlRotation = GetControlRotation();
		const FRotator YawRotation(0, ControlRotation.Yaw, 0);

		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void ASlashCharacter::EKeyPressed()
{
	AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
	if (OverlappingWeapon)
	{
		OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
		CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
	}
}

void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}


void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASlashCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASlashCharacter::MoveRight);
	PlayerInputComponent->BindAxis("Turn", this, &ASlashCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &ASlashCharacter::LookUp);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);// jump is defined in ACharacter
	PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &ASlashCharacter::EKeyPressed);
}

void ASlashCharacter::Turn(float Value)
{

	AddControllerYawInput(Value);
}
void ASlashCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value);
}

