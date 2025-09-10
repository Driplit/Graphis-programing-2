// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interfaces/HitInterface.h"
#include "Characters/CharacterTypes.h"
#include "Enemy.generated.h"

class UAnimMontage;
class UAtributeComponent;
class UHealthBarComponent;
	
UCLASS()
class HIGHLANDER_API AEnemy : public ACharacter, public IHitInterface
{
	GENERATED_BODY()

public:

	AEnemy();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetHit(const FVector& ImpactPoint) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:


	FTimerHandle DeathTimerHandle;

	UPROPERTY(VisibleAnywhere)
	UAtributeComponent* Attributes;
	
	UPROPERTY(VisibleAnywhere)
	UHealthBarComponent* HealthBarWidget;


	/**
	* Animation Montages
	**/

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* HitReactMontage;
	
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* DeathMontage;
protected:

	UPROPERTY(BlueprintReadOnly)
	EDeathPose DeathPose;

	virtual void BeginPlay() override;

	void Die();
	


	/**
	* Play Montage functions
	**/
	void PlayHitReactMontage(const FName& SectionName);


public:	

};
