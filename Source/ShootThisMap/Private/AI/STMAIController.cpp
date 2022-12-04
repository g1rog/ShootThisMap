
#include "AI/STMAIController.h"
#include "AI/STMAICharacter.h"
#include "Components/STMAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

ASTMAIController::ASTMAIController()
{
    STMAIPerceptionComponent = CreateDefaultSubobject<USTMAIPerceptionComponent>("STMPerceptionComponent");
    SetPerceptionComponent(*STMAIPerceptionComponent);

    bWantsPlayerState = true;
}

void ASTMAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    SetFocus(GetFocusOnActor());
}

void ASTMAIController::OnPossess(APawn *InPawn) 
{
    Super::OnPossess(InPawn);
    if (const auto STMCharacter = Cast<ASTMAICharacter>(InPawn))
        RunBehaviorTree(STMCharacter->BehaviorTreeAsset);
}

FORCEINLINE TObjectPtr<AActor> ASTMAIController::GetFocusOnActor() const 
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
