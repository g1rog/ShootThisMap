
#include "STMGameModeBase.h"
#include "Components/STMRespawnComponent.h"
#include "Player/STMBaseCharacter.h"
#include "Player/STMPlayerController.h"
#include "Player/STMPlayerState.h"
#include "UI/STMGameHUD.h"
#include "EngineUtils.h"
#include "AIController.h"
#include "STMUtils.h"

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
    SetMatchState(ESTMMatchState::InProgress);
}


UClass* ASTMGameModeBase::GetDefaultPawnClassForController_Implementation(AController *InController) 
{
    if (InController && InController->IsA<AAIController>())
        return AIPawnClass;
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

bool ASTMGameModeBase::SetPause(APlayerController *PC, FCanUnpause CanUnpauseDelegate)
{
    const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
    if (PauseSet)
        SetMatchState(ESTMMatchState::Pause);
    return PauseSet;
}

bool ASTMGameModeBase::ClearPause()
{
    const auto PauseCleared = Super::ClearPause();
    if (PauseCleared)
        SetMatchState(ESTMMatchState::InProgress);
    return PauseCleared;
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
        else
        {
            GameOver();
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
        PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
        SetPlayerColor(Controller);
        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor ASTMGameModeBase::SetColorByTeam(int32 TeamID) const
{
    return TeamID - 1 < GameData.TeamColors.Num() ?
        GameData.TeamColors[TeamID - 1] : GameData.DefaultTeamColor;
}

void ASTMGameModeBase::SetPlayerColor(const TObjectPtr<AController> &Controller) const
{
    if (!Controller) return;
    const auto Character = Cast<ASTMBaseCharacter>(Controller->GetPawn());

    if (!Character) return;
    const auto PlayerState = Cast<ASTMPlayerState>(Controller->PlayerState);

    if (!PlayerState) return;
    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void ASTMGameModeBase::Killed(const TObjectPtr<AController> &KillerController,
                              const TObjectPtr<AController> &VictimController)
{
    const auto KillerPlayerState = KillerController ? Cast<ASTMPlayerState>(KillerController->PlayerState) : nullptr;
    const auto VictimPlayerState = VictimController ? Cast<ASTMPlayerState>(VictimController->PlayerState) : nullptr;

    if (KillerPlayerState)
        KillerPlayerState->AddKill();
    if (VictimPlayerState)
        VictimPlayerState->AddDeath();
    
    StartRespawn(VictimController);
}

void ASTMGameModeBase::RespawnRequest(const TObjectPtr<AController> &Controller)
{
    ResetOnePlayer(Controller);
}

void ASTMGameModeBase::StartRespawn(const TObjectPtr<AController> &Controller) const
{
    const auto RespawnAvailable = RoundCountDown > GameData.MinRoundTimeForRespawn + GameData.RespawnTime;
    if (!RespawnAvailable) return;
    const auto RespawnComponent =
        STMUtils::GetSTMPlayerComponent<USTMRespawnComponent>(Controller);
    if (!RespawnComponent) return;
    RespawnComponent->Respawn(GameData.RespawnTime);
}

void ASTMGameModeBase::GameOver()
{
    for (const auto& Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }
    SetMatchState(ESTMMatchState::GameOver);
}

void ASTMGameModeBase::SetMatchState(ESTMMatchState State)
{
    if (MatchState == State) return;
    MatchState = State;
    OnMatchStateChanged.Broadcast(MatchState);
}


