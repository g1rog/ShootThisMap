
#include "UI/STMGameOverWidget.h"
#include "UI/STMPlayerStatRowWidget.h"
#include "Player/STMPlayerState.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STMGameModeBase.h"
#include "STMUtils.h"

void USTMGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (!GetWorld()) return;
    if (const auto GameMode = Cast<ASTMGameModeBase>(GetWorld()->GetAuthGameMode()))
        GameMode->OnMatchStateChanged.AddUObject(this, &USTMGameOverWidget::OnMatchStateChanged);
    if (ResetLevelButton)
        ResetLevelButton->OnClicked.AddDynamic(this, &USTMGameOverWidget::OnResetLevel);
}

void USTMGameOverWidget::OnResetLevel()
{
    const auto CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}

void USTMGameOverWidget::OnMatchStateChanged(ESTMMatchState State)
{
    if (State == ESTMMatchState::GameOver)
        UpdatePlayersStat();
}

void USTMGameOverWidget::UpdatePlayersStat() const
{
    if (!GetWorld() || !PlayerStatBox) return;
    PlayerStatBox->ClearChildren();
    
    for (auto Iterator = GetWorld()->GetControllerIterator(); Iterator; ++Iterator)
    {
        const auto Controller = Iterator->Get();
        if (!Controller) continue;
        
        const auto PlayerState = Cast<ASTMPlayerState>(Controller->PlayerState);
        if (!PlayerState) continue;
        
        const auto PlayerStatRowWidget = CreateWidget<USTMPlayerStatRowWidget>
            (GetWorld(), PlayerStatRowWidgetClass);
        if (!PlayerStatRowWidget) continue;

        PlayerStatRowWidget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        PlayerStatRowWidget->SetKills(STMUtils::TextFromInt(PlayerState->GetKillsNum()));
        PlayerStatRowWidget->SetDeaths(STMUtils::TextFromInt(PlayerState->GetDeathsNum()));
        PlayerStatRowWidget->SetTeam(STMUtils::TextFromInt(PlayerState->GetTeamID()));
        PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
        PlayerStatRowWidget->SetTeamColor(PlayerState->GetTeamColor());
        PlayerStatBox->AddChild(PlayerStatRowWidget);
    }
    
}

