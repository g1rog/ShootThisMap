
#include "Player/STMPlayerController.h"
#include "Components/STMRespawnComponent.h"
#include "STMGameModeBase.h"

ASTMPlayerController::ASTMPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USTMRespawnComponent>("RespawnComponent");
}

void ASTMPlayerController::BeginPlay()
{
    Super::BeginPlay();
    if (!GetWorld()) return;
    if (const auto GameMode = Cast<ASTMGameModeBase>(GetWorld()->GetAuthGameMode()))
        GameMode->OnMatchStateChanged.AddUObject(this, &ASTMPlayerController::OnMatchStateChanged);
}

void ASTMPlayerController::OnMatchStateChanged(ESTMMatchState State)
{
    if (State == ESTMMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}

void ASTMPlayerController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
    OnNewPawn.Broadcast(InPawn);
}

void ASTMPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    if (!InputComponent) return;
    InputComponent->BindAction("PauseGame", IE_Pressed, this, &ASTMPlayerController::OnPauseGame);
}

void ASTMPlayerController::OnPauseGame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    GetWorld()->GetAuthGameMode()->SetPause(this);
}
