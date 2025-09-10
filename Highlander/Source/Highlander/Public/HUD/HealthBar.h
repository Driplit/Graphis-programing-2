// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthBar.generated.h"

/**
 * 
 */
UCLASS()
class HIGHLANDER_API UHealthBar : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthBar;
	// Function to update the health bar
	/*UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateHealthBar(float CurrentHealth, float MaxHealth);*/
};
