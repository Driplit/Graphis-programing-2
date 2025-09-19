#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enemy/Enemy.h"
#include "CPPGame.generated.h"

class UEndGame;

UCLASS()
class HIGHLANDER_API ACPPGame : public AGameModeBase
{
    GENERATED_BODY()

public:
    ACPPGame();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    void CheckPlayerDead();
    void CheckForEnemies();
    void EndGame();

    bool bGameOver = false;

    UPROPERTY(EditDefaultsOnly, Category = Slash)
    TSubclassOf<UEndGame> EndGameWidgetClass;

    UPROPERTY()
	bool bIsPlayerDead = false; 

    UPROPERTY()
	bool bNoEnemiesLeft = false;

protected:



    UPROPERTY()
    int32 CurrentEnemies = 0;
};
