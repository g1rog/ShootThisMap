
#include "UI/STMPlayerStatRowWidget.h"
#include "Components/TextBLock.h"
#include "Components/Image.h"

FORCEINLINE void USTMPlayerStatRowWidget::SetPlayerName(const FText& Text) const
{
    if (!PlayerNameTextBlock) return;
    PlayerNameTextBlock->SetText(Text);
    
}

FORCEINLINE void USTMPlayerStatRowWidget::SetKills(const FText& Text) const
{
    if (!KillsTextBlock) return;
    KillsTextBlock->SetText(Text);
    
}

FORCEINLINE void USTMPlayerStatRowWidget::SetDeaths(const FText& Text) const
{
    if (!DeathsTextBlock) return;
    DeathsTextBlock->SetText(Text);
}

FORCEINLINE void USTMPlayerStatRowWidget::SetTeam(const FText& Text) const
{
    if (!TeamTextBlock) return;
    TeamTextBlock->SetText(Text);
}

FORCEINLINE void USTMPlayerStatRowWidget::SetPlayerIndicatorVisibility(const bool Visible) const
{
    if (!PlayerIndicatorImage) return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

FORCEINLINE void USTMPlayerStatRowWidget::SetTeamColor(const FLinearColor &Color) const
{
    if (!TeamImage) return;
    TeamImage->SetColorAndOpacity(Color);
}
