
#include "AI/STMAIController.h"
#include "AI/STMAICharacter.h"

void ASTMAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);
    
    const auto STMCharacter = Cast<ASTMAICharacter>(InPawn);
    if (STMCharacter)
        RunBehaviorTree(STMCharacter->BehaviorTreeAsset);
}
