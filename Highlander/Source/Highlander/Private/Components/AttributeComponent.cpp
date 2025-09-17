// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AttributeComponent.h"

// Sets default values for this component's properties
UAttributeComponent::UAttributeComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAttributeComponent::BeginPlay()
{
	Super::BeginPlay();

	
	
}

void UAttributeComponent::ReceiveDamage(float DamageAmount)
{
	CurHealth = FMath::Clamp(CurHealth - DamageAmount, 0.f, MaxHealth);
}

float UAttributeComponent::GetHealthPercent()
{
	return CurHealth / MaxHealth;
}
void UAttributeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	
}
bool UAttributeComponent::IsAlive()
{
	return CurHealth > 0.f;
}

