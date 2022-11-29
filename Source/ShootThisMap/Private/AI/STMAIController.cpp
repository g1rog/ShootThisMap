
#include "AI/STMAIController.h"
#include "AI/STMAICharacter.h"
#include "Components/STMAIPerceptionComponent.h"

ASTMAIController::ASTMAIController()
{
    STMAIPerceptionComponent = CreateDefaultSubobject<USTMAIPerceptionComponent>("STMPerceptionComponent");
    SetPerceptionComponent(*STMAIPerceptionComponent);
}

void ASTMAIController::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
    const auto AimActor = STMAIPerceptionComponent->GetClosestEnemy();
    SetFocus(AimActor);
}

void ASTMAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
    
    const auto STMCharacter = Cast<ASTMAICharacter>(InPawn);
    if (STMCharacter)
        RunBehaviorTree(STMCharacter->BehaviorTreeAsset);
}

