
#include "AI/Services/STMFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/STMAIPerceptionComponent.h"
#include "AIController.h"
#include "STMUtils.h"

USTMFindEnemyService::USTMFindEnemyService()
{
    NodeName = "Find Enemy";
}

void USTMFindEnemyService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, "find enemy");
    if (const auto Blackboard = OwnerComp.GetBlackboardComponent())
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent =
            STMUtils::GetSTMPlayerComponent<USTMAIPerceptionComponent>(Controller);
        if (PerceptionComponent)
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
