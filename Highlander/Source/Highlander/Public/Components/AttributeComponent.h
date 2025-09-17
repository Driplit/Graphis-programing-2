// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AttributeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HIGHLANDER_API UAttributeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	
	UAttributeComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float CurHealth;
	
	UPROPERTY(EditAnywhere, Category = "Actor Attributes")
	float MaxHealth;

public:
	void ReceiveDamage(float DamageAmount);
	float GetHealthPercent();
	
	bool IsAlive();

		
};
