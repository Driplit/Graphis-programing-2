// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/SlashHUD.h"
#include "HUD/GameOverlay.h"
#include "HUD/EndGame.h"
void ASlashHUD::BeginPlay()
{
	Super::BeginPlay();
	UWorld* World = GetWorld();
	if (World)
	{
		APlayerController* Controller = World->GetFirstPlayerController();
		if(Controller && GameOverlayClass)
		{
			GameOverlay = CreateWidget<UGameOverlay>(Controller, GameOverlayClass);
			GameOverlay->AddToViewport();
		}
	}
}
