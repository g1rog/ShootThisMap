
#include "STMGameModeBase.h"
#include "AIController.h"
#include "Player/STMBaseCharacter.h"
#include "Player/STMPlayerController.h"
#include "Player/STMPlayerState.h"
#include "UI/STMGameHUD.h"

ASTMGameModeBase::ASTMGameModeBase()
{
    DefaultPawnClass = ASTMBaseCharacter::StaticClass();
    PlayerControllerClass = ASTMPlayerController::StaticClass();
    HUDClass = ASTMGameHUD::StaticClass();
    PlayerStateClass = ASTMPlayerState::StaticClass();
}

void ASTMGameModeBase::StartPlay() 
{
    Super::StartPlay();
    SpawnBots();
    CreateTeamsInfo();
    CurrentRound = 1;
    StartRound();
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

void ASTMGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &ASTMGameModeBase::GameTimerUpdate, 1.0f, true);
    
}

void ASTMGameModeBase::GameTimerUpdate()
{
    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);
        if (CurrentRound + 1 <= GameData.RoundsNum)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
    }
}

void ASTMGameModeBase::ResetPlayers()
{
    if (!GetWorld()) return;
    for (auto Iterator = GetWorld()->GetControllerIterator(); Iterator; ++Iterator)
        ResetOnePlayer(Iterator->Get());
}

void ASTMGameModeBase::ResetOnePlayer(const TObjectPtr<AController> &Controller)
{
    if (Controller && Controller->GetPawn())
        Controller->GetPawn()->Reset();
    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void ASTMGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld()) return;
    int32 TeamID = 1;
    for (auto Iterator = GetWorld()->GetControllerIterator(); Iterator; ++Iterator)
    {
        const auto Controller = Iterator->Get();
        if (!Controller) continue;
        const auto PlayerState = Cast<ASTMPlayerState>(Controller->PlayerState);
        if (!Controller) continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(SetColorByTeam(TeamID));
        SetPlayerColor(Controller);
        TeamID = TeamID == 1 ? 2 : 1;
    }

}

FLinearColor ASTMGameModeBase::SetColorByTeam(int32 TeamID) const
{
    return TeamID - 1 < GameData.TeamColors.Num() ?
        GameData.TeamColors[TeamID - 1] : GameData.DefaultTeamColor;
}

void ASTMGameModeBase::SetPlayerColor(const TObjectPtr<AController> &Controller)
{
    if (!Controller) return;
    const auto Character = Cast<ASTMBaseCharacter>(Controller->GetPawn());

    if (!Character) return;
    const auto PlayerState = Cast<ASTMPlayerState>(Controller->PlayerState);

    if (!PlayerState) return;
    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

