#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Enemy/Enemy.h"
#include "CPPGame.generated.h"

UCLASS()
class HIGHLANDER_API ACPPGame : public AGameModeBase
{
    GENERATED_BODY()

public:
    ACPPGame();

    virtual void BeginPlay() override;
    virtual void Tick(float DeltaTime) override;

    void CheckForEnemies();

    void EndGame();

  

protected:

    /*UPROPERTY()
    TArray<AEnemy*> FoundEnemies;*/


    UPROPERTY()
    int32 CurrentEnemies = 0;
};
