
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STMFireService.generated.h"

UCLASS()
class SHOOTTHISMAP_API USTMFireService : public UBTService
{
	GENERATED_BODY()

public:
    USTMFireService();

protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    
private:

public:
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

private:
    
	
};
