#include "CPPGame.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "HUD/SlashHUD.h"
#include "Enemy/Enemy.h"
#include "Components/AttributeComponent.h"
#include "HUD/EndGame.h"

ACPPGame::ACPPGame()
{
    PrimaryActorTick.bCanEverTick = true;

    // --- Set Default Pawn ---
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_SlashCharacter"));
    if (PlayerPawnBPClass.Succeeded())
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }

    // --- Set HUD ---
    HUDClass = ASlashHUD::StaticClass();

    // --- Set EndGame Widget ---
    static ConstructorHelpers::FClassFinder<UUserWidget> EndGameWidgetBP(TEXT("/Game/Blueprints/HUD/WBP_EndGame"));
    if (EndGameWidgetBP.Succeeded())
    {
        EndGameWidgetClass = EndGameWidgetBP.Class;
    }
}

void ACPPGame::BeginPlay()
{
    Super::BeginPlay();
    
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PC) return;

    
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundEnemies);

    CurrentEnemies = FoundEnemies.Num();
}

void ACPPGame::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    CheckPlayerDead();
    CheckForEnemies();
}

void ACPPGame::CheckPlayerDead()
{
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)
    {
        UAttributeComponent* AttrComp = PlayerPawn->FindComponentByClass<UAttributeComponent>();
        if (AttrComp && !AttrComp->IsAlive())
        {
            bIsPlayerDead = true;
            EndGame();
        }
    }
}

void ACPPGame::CheckForEnemies()
{
    TArray<AActor*> FoundEnemies;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundEnemies);

    if (CurrentEnemies != FoundEnemies.Num())
    {
        CurrentEnemies = FoundEnemies.Num();
        if (CurrentEnemies == 0)
        {
            bNoEnemiesLeft = true;
            EndGame();
        }
    }
}

void ACPPGame::EndGame()
{
    if (bGameOver) return;
    bGameOver = true;

    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (!PC) return;

    if (PC->GetPawn())
    {
        PC->GetPawn()->DisableInput(PC);
    }

    UGameplayStatics::SetGamePaused(GetWorld(), true);

    PC->bShowMouseCursor = true;
    FInputModeUIOnly InputMode;
    InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    PC->SetInputMode(InputMode);

    if (EndGameWidgetClass)
    {
        UEndGame* EndGameWidget = CreateWidget<UEndGame>(PC, EndGameWidgetClass);
        if (EndGameWidget)
        {
            EndGameWidget->AddToViewport(100);

            if (bIsPlayerDead)
            {
                EndGameWidget->SetResultMessage(TEXT("YOU LOSE"));
            }
            else if (bNoEnemiesLeft)
            {
                EndGameWidget->SetResultMessage(TEXT("YOU WIN"));
            }
            else
            {
                EndGameWidget->SetResultMessage(TEXT("GAME OVER"));
            }
        }
    }
    FInputModeGameOnly GameInput;
    PC->SetInputMode(GameInput);
}
