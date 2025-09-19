// Fill out your copyright...

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"	
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class AItem;
class UAnimMontage;
class UGameOverlay;

UCLASS()
class HIGHLANDER_API ASlashCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:

	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	void SetHUDHealth();


	

	

protected:
	virtual void BeginPlay() override;

	void InitializeGameOverlay();

	// --- Movement ---
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	// --- Interact ---
	void EKeyPressed(); // to pickup weapons or items

	// --- Combat ---
	virtual void Attack() override;
	void HeavyAttack();
	virtual void PlayAttackMontage() override;
	void ResetCombo();

	
	virtual void AttackEnd() override;

	virtual bool CanAttack() override;



	// Called by anim notifies in montage
	UFUNCTION(BlueprintCallable)
	void EnableCombo();

	/*UFUNCTION(BlueprintCallable)
	void DisableCombo();*/


	void PlayEquipMontage(const FName& SectionName);
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

	

	

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* EquipMontage;

	// --- Combo State ---
	int32 ComboIndex = 0;              // 0 = not attacking, 1 = Attack1, etc.
	bool bCanCombo = false;            // True if player can chain to the next attack
	bool bComboInputBuffered = false;  // If player pressed attack during combo window
	FTimerHandle ComboResetTimer;

	UPROPERTY()
	UGameOverlay* GameOverlay;

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
