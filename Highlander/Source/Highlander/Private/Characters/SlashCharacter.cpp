// Fill out your copyright...

#include "Characters/SlashCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Items/Item.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimInstance.h"
#include "Components/BoxComponent.h"

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

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Equip", IE_Pressed, this, &ASlashCharacter::EKeyPressed);
    PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ASlashCharacter::Attack);
    PlayerInputComponent->BindAction("HeavyAttack", IE_Pressed, this, &ASlashCharacter::HeavyAttack);
}

void ASlashCharacter::SetWeaponCollisionEnabled(ECollisionEnabled::Type CollisionEnabled)
{
    if (EquippedWeapon && EquippedWeapon->GetWeaponBox())
    {
        EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionEnabled);
        EquippedWeapon->IgnoreActors.Empty();
    }
}

void ASlashCharacter::MoveForward(float Value)
{
    if (Controller && (Value != 0.0f))
    {
        const FRotator ControlRotation = GetControlRotation();
        const FRotator YawRotation(0, ControlRotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
        AddMovementInput(Direction, Value);
    }
}

void ASlashCharacter::MoveRight(float Value)
{
    if (Controller && (Value != 0.0f))
    {
        const FRotator ControlRotation = GetControlRotation();
        const FRotator YawRotation(0, ControlRotation.Yaw, 0);

        const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
        AddMovementInput(Direction, Value);
    }
}

void ASlashCharacter::Turn(float Value)
{
    AddControllerYawInput(Value);
}

void ASlashCharacter::LookUp(float Value)
{
    AddControllerPitchInput(Value);
}

void ASlashCharacter::EKeyPressed()
{
    AWeapon* OverlappingWeapon = Cast<AWeapon>(OverlappingItem);
    if (OverlappingWeapon)
    {
        OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"), this, this);
        CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
		OverlappingItem = nullptr;
		EquippedWeapon = OverlappingWeapon;
    }
    else
    {
        if(CanStowWeapon())
        {
			PlayEquipMontage(FName("StowWeapon"));
            CharacterState = ECharacterState::ECS_Unequipped;
        }
        else if(CanArmWeapon())
		{
            PlayEquipMontage(FName("ArmWeapon"));
			CharacterState = ECharacterState::ECS_EquippedOneHandedWeapon;
		}
    }
}

void ASlashCharacter::Attack()
{
	
    if(CanAttack())
    {
        PlayAttackMontage();
        ActionState = EActionState::EAS_Attacking;
    }
	
}

bool ASlashCharacter::CanAttack() const
{
    
    return ActionState == EActionState::EAS_Unoccupied && CharacterState != ECharacterState::ECS_Unequipped;
}



bool ASlashCharacter::CanStowWeapon() const
{
    return ActionState == EActionState::EAS_Unoccupied &&
        CharacterState != ECharacterState::ECS_Unequipped &&
        EquipMontage;
}

bool ASlashCharacter::CanArmWeapon() const
{
    return ActionState == EActionState::EAS_Unoccupied &&
        CharacterState == ECharacterState::ECS_Unequipped &&
        EquippedWeapon;
}

void ASlashCharacter::HeavyAttack()
{
    if (!AttackMontage) return;

    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (!AnimInstance) return;

    // Play the HeavyAttack section of the montage
    AnimInstance->Montage_Play(AttackMontage);
    AnimInstance->Montage_JumpToSection(FName("HeavyAttack"), AttackMontage);

    ActionState = EActionState::EAS_Attacking;

}

void ASlashCharacter::PlayAttackMontage()
{
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (!AnimInstance || !AttackMontage) return;

    // If inside combo window → buffer input
    if (bCanCombo)
    {
        bComboInputBuffered = true;
        return;
    }

    // Determine next combo step
    ComboIndex++;
    FName SectionName;

    switch (ComboIndex)
    {
    case 1:
        SectionName = "Attack1";
        break;
    case 2:
        SectionName = "Attack2";
        break;
    case 3:
        SectionName = "Attack3";
        break;
    default:
        ResetCombo();
        return;
    }

    // Play the attack montage section
    AnimInstance->Montage_Play(AttackMontage);
    AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);

    // Disable combo until next allowed window
    bCanCombo = false;

    // Start/reset the combo timeout timer
    GetWorldTimerManager().ClearTimer(ComboResetTimer);
    GetWorldTimerManager().SetTimer(ComboResetTimer, this, &ASlashCharacter::ResetCombo, 1.0f, false);
}

void ASlashCharacter::PlayEquipMontage(const FName& SectionName)
{
    UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
    if (!AnimInstance || !EquipMontage) return;

	UE_LOG(LogTemp, Warning, TEXT("No equip montage or anim instance"));
    AnimInstance->Montage_Play(EquipMontage);
    AnimInstance->Montage_JumpToSection(SectionName, EquipMontage);
	ActionState = EActionState::EAS_Equipping;
}

void ASlashCharacter::EnableCombo()
{
    bCanCombo = true;
    UE_LOG(LogTemp, Warning, TEXT("Combo window enabled"));


    if (bComboInputBuffered)
    {
        Attack(); // Immediately continue combo if buffered
        bComboInputBuffered = false;
    }
}

void ASlashCharacter::DisableCombo()
{
    bCanCombo = false;
}

void ASlashCharacter::ResetCombo()
{
    ComboIndex = 0;
    bCanCombo = false;
    bComboInputBuffered = false;
}

void ASlashCharacter::AttackEnd()
{
    UE_LOG(LogTemp, Warning, TEXT("Attack ended"));
    ActionState = EActionState::EAS_Unoccupied;
}


