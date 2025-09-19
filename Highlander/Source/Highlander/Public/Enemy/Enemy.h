// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseCharacter.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"

class UAnimMontage;
class UHealthBarComponent;
class UPawnSensingComponent;



UCLASS()
class HIGHLANDER_API AEnemy : public ABaseCharacter
{
	GENERATED_BODY()
	
public:

	AEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetHit_Implementation(const FVector& ImpactPoint) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	
	
	

private:



	FTimerHandle DeathTimerHandle;
	
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;

	UPROPERTY(VisibleAnywhere)
	UPawnSensingComponent* PawnSensing;


	UPROPERTY()
	AActor* CombatTarget;

	UPROPERTY(EditAnywhere)
	double CombatRadius = 500.f;

	bool InTargetRange(AActor* Target, double Radius);


	UPROPERTY(EditAnywhere)
	double AttackRadius = 200.f;


	UPROPERTY()
	class AAIController* EnemyController;

	//current target to move to
	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	AActor* PatrolTarget;


	UPROPERTY(EditInstanceOnly, Category = "AI Navigation")
	TArray<AActor*> PatrolTargets;

	UPROPERTY(EditAnywhere)
	double PatrolRadius = 200.f;

	EEnemyState EnemyState = EEnemyState::EES_Patrolling;

	FTimerHandle PatrolTimer;
	void PatrolTimerFinished();

	UPROPERTY(EditAnywhere, Category = "AI Navigation")	
	float WaitMin = 3.f;
	UPROPERTY(EditAnywhere, Category = "AI Navigation")
	float WaitMax = 5.f;

	UPROPERTY(EditAnyWhere)
	TSubclassOf<class AWeapon> WeaponClass;



protected:

	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose;

	virtual void BeginPlay() override;

	void MoveToTarget(AActor* Target);

	AActor* ChoosePatrolTarget();	
	virtual void Die()override;
	
	UFUNCTION()
	void PawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void CheckCombatTarget();

	UFUNCTION()
	void CheckPatrolTarget();

	virtual void Attack() override;
	virtual void PlayAttackMontage() override;

	


public:	

};
