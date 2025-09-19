#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"
/**
 * Main menu widget
 */
UCLASS()
class HIGHLANDER_API UMainMenu : public UUserWidget
{
    GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* StartButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitButton;

private:
	UFUNCTION()
	void OnStartClicked();

	UFUNCTION()
	void OnQuitClicked();


};
