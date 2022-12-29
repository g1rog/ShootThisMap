
#include "UI/STMSpectatorWidget.h"
#include "Components/STMRespawnComponent.h"
#include "STMUtils.h"

bool USTMSpectatorWidget::GetRespawnTime(int32 &CountDownTime) const
{
    const auto RespawnComponent =
        STMUtils::GetSTMPlayerComponent<USTMRespawnComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;
    CountDownTime = RespawnComponent->GetRespawnCountDown();
    return true;
}
