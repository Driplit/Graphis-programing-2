// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GameOverlay.generated.h"

/**
 * 
 */
UCLASS()
class HIGHLANDER_API UGameOverlay : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void SetHealthPercent(float Percent);
	void SetKills(int32 Kills);



private:

	UPROPERTY(meta = (BindWidget))
	class UProgressBar* HealthProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* KillsText;
};
