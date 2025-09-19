#include "CPPGame.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"
#include "HUD/SlashHUD.h"
#include "Enemy/Enemy.h"
#include "Components/AttributeComponent.h"


ACPPGame::ACPPGame()
{
    PrimaryActorTick.bCanEverTick = true;

    // Correct Default Pawn path
    static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Blueprints/Characters/BP_SlashCharacter"));
    if (PlayerPawnBPClass.Succeeded())
    {
        DefaultPawnClass = PlayerPawnBPClass.Class;
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to find BP_SlashCharacter!"));
    }

    HUDClass = ASlashHUD::StaticClass();
}


void ACPPGame::BeginPlay()
{
    Super::BeginPlay();

    
    TArray<AActor*> FoundEnemies;
    // Get all actors of class AEnemy
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundEnemies);

    // Print number of enemies to screen
    int32 NumEnemies = FoundEnemies.Num();
	CurrentEnemies = NumEnemies;
    if (GEngine)
    {
        GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
            FString::Printf(TEXT("Number of enemies in the world: %d"), NumEnemies));
    }
}

void ACPPGame::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // --- Player death check ---
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
    if (PlayerPawn)
    {
        UAttributeComponent* AttrComp = PlayerPawn->FindComponentByClass<UAttributeComponent>();
        if (AttrComp && !AttrComp->IsAlive())
        {
            EndGame();
            UE_LOG(LogTemp, Warning, TEXT("Player is dead!"));
        }
    }

    // --- Enemy count check ---
    CheckForEnemies();
}

void ACPPGame::CheckForEnemies()
{
    TArray<AActor*> FoundEnemies;

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), AEnemy::StaticClass(), FoundEnemies);

    if (CurrentEnemies != FoundEnemies.Num())
    {
        CurrentEnemies = FoundEnemies.Num();
        if (GEngine)
        {
            GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green,
                FString::Printf(TEXT("Number of enemies in the world: %d"), CurrentEnemies));
        }
    }
}
void ACPPGame::EndGame()
{
    UE_LOG(LogTemp, Warning, TEXT("Game Over!"));

    // Option 1: Disable player input
    APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    if (PC && PC->GetPawn())
    {
        PC->GetPawn()->DisableInput(PC);
    }

    // Option 2: Show Game Over UI (if you have a HUD)
    // Example: Cast<ASlashHUD>(PC->GetHUD())->ShowGameOver();

    // Option 3: Stop the game completely
    UGameplayStatics::SetGamePaused(GetWorld(), true);
}

