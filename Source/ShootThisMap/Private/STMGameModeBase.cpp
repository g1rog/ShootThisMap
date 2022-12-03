
#include "STMGameModeBase.h"
#include "AIController.h"
#include "Player/STMBaseCharacter.h"
#include "Player/STMPlayerController.h"

ASTMGameModeBase::ASTMGameModeBase()
{
    DefaultPawnClass = ASTMBaseCharacter::StaticClass();
    PlayerControllerClass = ASTMPlayerController::StaticClass();
}

void ASTMGameModeBase::StartPlay() 
{
    Super::StartPlay();
    SpawnBots();
}


UClass* ASTMGameModeBase::GetDefaultPawnClassForController_Implementation(AController *InController) 
{
    if (InController && InController->IsA<AAIController>())
        return AIPawnClass;

    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void ASTMGameModeBase::SpawnBots()
{
    if (!GetWorld()) return;
    for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        const auto STMAIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(STMAIController);
    }
}
