
#include "AI/Services/STMFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STMWeaponComponent.h"
#include "AIController.h"
#include "STMUtils.h"

USTMFireService::USTMFireService()
{
    NodeName = "Fire";
}

void USTMFireService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);
    if (const auto Controller = OwnerComp.GetAIOwner())
    {
        if (const auto WeaponComponent =
            STMUtils::GetSTMPlayerComponent<USTMWeaponComponent>(Controller->GetPawn()))
                HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}




