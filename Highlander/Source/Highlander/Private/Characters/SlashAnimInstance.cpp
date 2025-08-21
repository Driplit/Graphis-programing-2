// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashAnimInstance.h"
#include "Characters/SlashCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

void USlashAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	
	SlashCharacter = Cast<ASlashCharacter>(TryGetPawnOwner());
	if(SlashCharacter)
	{
		CharacterMovement = SlashCharacter->GetCharacterMovement();
	}
	
}

void USlashAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	
	if (CharacterMovement)
	{
		GroundSpeed = UKismetMathLibrary::VSizeXY(CharacterMovement->Velocity);
		IsFalling = CharacterMovement->IsFalling();
		CharacterState = SlashCharacter->GetCharacterState();
	}
}