
#include "UI/STMHealthBarWidget.h"
#include "Components/ProgressBar.h"

void USTMHealthBarWidget::SetHealthPercent(const float Percent) const
{
    if (!HealthProgressBar) return;
    const auto HealthBarVisibility = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent))
        ? ESlateVisibility::Hidden : ESlateVisibility::Visible;
    HealthProgressBar->SetVisibility(HealthBarVisibility);
    const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);
    HealthProgressBar->SetPercent(Percent);
}
