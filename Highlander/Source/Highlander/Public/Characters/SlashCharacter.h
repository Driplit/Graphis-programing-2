// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterTypes.h"
#include "SlashCharacter.generated.h"


class USpringArmComponent;
class UCameraComponent;
class AItem;





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
	void MoveForward(float Value);
	void Turn(float Value);
	void LookUp(float Value);
	void MoveRight(float Value);
	void EKeyPressed();
	//attack
	//dodge/roll
	//use item

	

private:

	ECharacterState CharacterState = ECharacterState::ECS_Unequipped ;

	UPROPERTY(VIsibleAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(VIsibleAnywhere)
	UCameraComponent* ViewCamera;

	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappingItem;

public:
	FORCEINLINE void SetOverlappingItem(AItem* Item) { OverlappingItem = Item; }//only use with getters and setters
	FORCEINLINE ECharacterState GetCharacterState() const { return CharacterState; }
};
