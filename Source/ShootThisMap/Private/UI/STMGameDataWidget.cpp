
#include "UI/STMGameDataWidget.h"
#include "Player/STMPlayerState.h"
#include "STMGameModeBase.h"

int32 USTMGameDataWidget::GetCurrentRoundNum() const
{
    const auto GameMode = GetSTMGameMode();
    return GameMode ? GameMode->GetCurrentRoundNum() : 0;
}

int32 USTMGameDataWidget::GetTotalRoundsNum() const
{
    const auto GameMode = GetSTMGameMode();
    return GameMode ? GameMode->GetGameData().RoundsNum : 0;
}

int32 USTMGameDataWidget::GetRoundSecondsRemaining() const
{
    const auto GameMode = GetSTMGameMode();
    return GameMode ? GameMode->GetRoundSecondsRemaining() : 0;
}

FORCEINLINE TObjectPtr<ASTMGameModeBase> USTMGameDataWidget::GetSTMGameMode() const
{
    return GetWorld() ? Cast<ASTMGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

FORCEINLINE TObjectPtr<ASTMPlayerState> USTMGameDataWidget::GetSTMPlayerState() const
{
    return GetOwningPlayer() ? Cast<ASTMPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}
