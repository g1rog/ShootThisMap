
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STMHealthPercentDecorator.generated.h"

UCLASS()
class SHOOTTHISMAP_API USTMHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:
    USTMHealthPercentDecorator();
    
protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

public:
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthPercent = 0.6f;
    
};
