// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/GameOverlay.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"


void UGameOverlay::SetHealthPercent(float Percent)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Percent);
	}
}

void UGameOverlay::SetKills(int32 Kills)
{
	if (KillsText)
	{
		KillsText->SetText(FText::AsNumber(Kills));
	}
}
