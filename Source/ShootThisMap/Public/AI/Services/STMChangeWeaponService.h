
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STMChangeWeaponService.generated.h"

UCLASS()
class SHOOTTHISMAP_API USTMChangeWeaponService : public UBTService
{
	GENERATED_BODY()

public:
    USTMChangeWeaponService();
    
protected:
    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
    
private:

public:
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Probability = 0.5f;

private:
    
};
