
#include "UI/STMPlayerStatRowWidget.h"
#include "Components/TextBLock.h"
#include "Components/Image.h"

void USTMPlayerStatRowWidget::SetPlayerName(const FText& Text) const
{
    if (!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(Text);
}

void USTMPlayerStatRowWidget::SetKills(const FText& Text) const
{
    if (!KillsTextBlock) return;
    KillsTextBlock->SetText(Text);
}

void USTMPlayerStatRowWidget::SetDeaths(const FText& Text) const
{
    if (!DeathsTextBlock) return;
    DeathsTextBlock->SetText(Text);
}

void USTMPlayerStatRowWidget::SetTeam(const FText& Text) const
{
    if (!TeamTextBlock) return;
    TeamTextBlock->SetText(Text);
}

void USTMPlayerStatRowWidget::SetPlayerIndicatorVisibility(const bool Visible) const
{
    if (!PlayerIndicatorImage) return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTMPlayerStatRowWidget::SetTeamColor(const FLinearColor &Color) const
{
    if (!TeamImage) return;
    TeamImage->SetColorAndOpacity(Color);
}
