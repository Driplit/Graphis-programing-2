// Fill out your copyright...

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AItem;
class UAnimMontage;
class AWeapon;

UCLASS()
class HIGHLANDER_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	// --- Movement ---
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	// --- Interact ---
	void EKeyPressed(); // to pickup weapons or items

	// --- Combat ---
	void Attack();
	void HeavyAttack();
	void PlayAttackMontage();
	void ResetCombo();

	UFUNCTION(BlueprintCallable)
	void AttackEnd();

	bool CanAttack() const;



	// Called by anim notifies in montage
	UFUNCTION(BlueprintCallable) void EnableCombo();
	UFUNCTION(BlueprintCallable) void DisableCombo();


	void PlayEquipMontage(FName SectionName);
	bool CanStowWeapon() const;
	bool CanArmWeapon() const;

private:
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;
	EActionState ActionState = EActionState::EAS_Unoccupied;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

	UPROPERTY(VisibleInstanceOnly, Category = Weapon)
	AWeapon* EquippedWeapon;

	// --- Animation ---
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

	// --- Combo State ---
	int32 ComboIndex = 0;              // 0 = not attacking, 1 = Attack1, etc.
	bool bCanCombo = false;            // True if player can chain to the next attack
	bool bComboInputBuffered = false;  // If player pressed attack during combo window
	FTimerHandle ComboResetTimer;

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
