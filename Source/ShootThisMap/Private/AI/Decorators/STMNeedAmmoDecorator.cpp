
#include "AI/Decorators/STMNeedAmmoDecorator.h"
#include "Components/STMWeaponComponent.h"
#include "AIController.h"
#include "STMUtils.h"

USTMNeedAmmoDecorator::USTMNeedAmmoDecorator()
{
    NodeName = "Need Ammo";
}

bool USTMNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const 
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;
    const auto WeaponComponent =
        STMUtils::GetSTMPlayerComponent<USTMWeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent) return false;
    return WeaponComponent->NeedAmmo(WeaponType);
}
