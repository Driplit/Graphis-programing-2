#include "UI/MainMenu.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();
	if (StartButton)
	{
		StartButton->OnClicked.AddDynamic(this, &UMainMenu::OnStartClicked);
	}
	if (QuitButton)
	{
		QuitButton->OnClicked.AddDynamic(this, &UMainMenu::OnQuitClicked);
	}
}

void UMainMenu::OnStartClicked()
{
	UGameplayStatics::OpenLevel(this, FName("M_DevMap"));
}

void UMainMenu::OnQuitClicked()
{
	UKismetSystemLibrary::QuitGame(this, nullptr, EQuitPreference::Quit, true);
}
