// Fill out your copyright notice in the Description page of Project Settings.


#include "HUD/EndGame.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"


void UEndGame::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	if (RestartButton)
	{
		RestartButton->OnClicked.AddDynamic(this, &UEndGame::OnRestartClicked);
	}
	if (MainMenuButton)
	{
		MainMenuButton->OnClicked.AddDynamic(this, &UEndGame::OnMainMenuClicked);
	}
}

void UEndGame::OnMainMenuClicked()
{
	UWorld* World = GetWorld();
	if (World)
	{
		// Replace "MainMenuMap" with your actual main menu map name
		UGameplayStatics::OpenLevel(World, FName("M_MainMenuMap"));
	}
}
void UEndGame::OnRestartClicked()
{
	UWorld* World = GetWorld();
	if (World)
	{
		UGameplayStatics::OpenLevel(World, FName("M_MDevMap"));
	}
}

void UEndGame::SetResultMessage(const FString& Message)
{
	if (ResultText)
	{
		ResultText->SetText(FText::FromString(Message));
	}
}
