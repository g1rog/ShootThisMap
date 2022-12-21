
#include "UI/STMGameHUD.h"
#include "UI/STMBaseWidget.h"
#include "STMGameModeBase.h"

void ASTMGameHUD::BeginPlay()
{
    Super::BeginPlay();
    
    GameWidgets.Add(ESTMMatchState::InProgress, CreateWidget<USTMBaseWidget>
        (GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(ESTMMatchState::Pause, CreateWidget<USTMBaseWidget>
       (GetWorld(), PauseWidgetClass));
    GameWidgets.Add(ESTMMatchState::GameOver, CreateWidget<USTMBaseWidget>
      (GetWorld(), GameOverWidgetClass));

    for (const auto& GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget) continue;
        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }
    if (!GetWorld()) return;
    if (const auto GameMode = Cast<ASTMGameModeBase>(GetWorld()->GetAuthGameMode()))
        GameMode->OnMatchStateChanged.AddUObject(this, &ASTMGameHUD::OnMatchStateChanged);
}

void ASTMGameHUD::OnMatchStateChanged(ESTMMatchState State)
{
    if (CurrentWidget)
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    if (GameWidgets.Contains(State))
        CurrentWidget = GameWidgets[State];
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
        CurrentWidget->Show();
    }
    
    GEngine->AddOnScreenDebugMessage(1, 5.0f, FColor::Green, *UEnum::GetValueAsString(State));
}
