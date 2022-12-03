
#include "AI/Services/STMChangeWeaponService.h"
#include "Components/STMWeaponComponent.h"
#include "AIController.h"
#include "STMUtils.h"

USTMChangeWeaponService::USTMChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void USTMChangeWeaponService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) 
{
    if (const auto Controller = OwnerComp.GetAIOwner())
    {
        const auto WeaponComponent = STMUtils::GetSTMPlayerComponent<USTMWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
            WeaponComponent->NextWeapon();
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}


