
#include "AI/Decorators/STMHealthPercentDecorator.h"
#include "Components/STMHealthComponent.h"
#include "AIController.h"
#include "STMUtils.h"

USTMHealthPercentDecorator::USTMHealthPercentDecorator()
{
    NodeName = "Health Percent";
}

bool USTMHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false; 
    const auto HealthComponent =
        STMUtils::GetSTMPlayerComponent<USTMHealthComponent>(Controller);
    if (!HealthComponent || HealthComponent->IsDead()) return false;
    return HealthComponent->GetHealthPercent() <= HealthPercent;
}

