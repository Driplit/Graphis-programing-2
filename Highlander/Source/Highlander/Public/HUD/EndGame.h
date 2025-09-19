#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndGame.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class HIGHLANDER_API UEndGame : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ResultText;

	
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenuButton;

	UFUNCTION()
	void OnRestartClicked();

	UFUNCTION()
	void OnMainMenuClicked();

public:

	
	void SetResultMessage(const FString& Message);
};
