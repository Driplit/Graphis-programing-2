// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SlashHUD.generated.h"

/**
 * 
 */
class UGameOverlay;
class UEndGame;

UCLASS()
class HIGHLANDER_API ASlashHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = Slash)
	TSubclassOf<UGameOverlay> GameOverlayClass;

	UPROPERTY()
	UGameOverlay* GameOverlay;

	

	UPROPERTY()
	UEndGame* EndGameWidget;

public:
	
	FORCEINLINE UGameOverlay* GetGameOverlay() const { return GameOverlay; }

};
