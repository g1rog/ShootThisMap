
#include "Components/STMAIPerceptionComponent.h"
#include "Components/STMHealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"
#include "AIController.h"
#include "STMUtils.h"

TObjectPtr<AActor> USTMAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<TObjectPtr<AActor>> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);

    if (PercieveActors.Num() == 0)
    {
        GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);
        if (PercieveActors.Num() == 0) return nullptr;
    }
	
    const auto Controller = Cast<AAIController>(GetOwner());
    if (!Controller) return nullptr;
    const auto Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;
    float BestDistance = MAX_FLT;
    TObjectPtr<AActor> BestPawn = nullptr;

    for (const auto& PercieveActor : PercieveActors)
    {
        const auto PercievePawn = Cast<APawn>(PercieveActor);
        const auto HealthComponent =
            STMUtils::GetSTMPlayerComponent<USTMHealthComponent>(PercieveActor);
        const auto AreEnemies = PercievePawn &&
            STMUtils::AreEnemies(Controller, PercievePawn->Controller);
        
        if (HealthComponent && !HealthComponent->IsDead() && AreEnemies)
        {
            const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PercieveActor;
            }
        }
    }
    return BestPawn;
}
