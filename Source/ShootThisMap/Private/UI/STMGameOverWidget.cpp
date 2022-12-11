
#include "UI/STMGameOverWidget.h"
#include "UI/STMPlayerStatRowWidget.h"
#include "Player/STMPlayerState.h"
#include "Components/VerticalBox.h"
#include "STMGameModeBase.h"
#include "STMUtils.h"

bool USTMGameOverWidget::Initialize()
{
    if (!GetWorld()) return false;
    if (const auto GameMode = Cast<ASTMGameModeBase>(GetWorld()->GetAuthGameMode()))
        GameMode->OnMatchStateChanged.AddUObject(this, &USTMGameOverWidget::OnMatchStateChanged);
    return Super::Initialize();
}

void USTMGameOverWidget::OnMatchStateChanged(ESTMMatchState State)
{
    if (State == ESTMMatchState::GameOver)
        UpdatePlayersStat();
}

void USTMGameOverWidget::UpdatePlayersStat()
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
        PlayerStatBox->AddChild(PlayerStatRowWidget);
    }
    
}


