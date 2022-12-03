
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STMFindEnemyService.generated.h"

UCLASS()
class SHOOTTHISMAP_API USTMFindEnemyService : public UBTService
{
	GENERATED_BODY()
public:
    USTMFindEnemyService();
protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:

public:
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

private:
    
};
