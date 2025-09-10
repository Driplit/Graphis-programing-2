// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AtributeComponent.h"

// Sets default values for this component's properties
UAtributeComponent::UAtributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAtributeComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void UAtributeComponent::ReceiveDamage(float DamageAmount)
{
	CurHealth = FMath::Clamp(CurHealth - DamageAmount, 0.f, MaxHealth);
}

float UAtributeComponent::GetHealthPercent()
{
	return CurHealth / MaxHealth;
}
void UAtributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}
bool UAtributeComponent::IsAlive()
{
	return CurHealth > 0.f;
}

