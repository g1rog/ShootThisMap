
#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STMNeedAmmoDecorator.generated.h"

class ASTMBaseWeapon;

UCLASS()
class SHOOTTHISMAP_API USTMNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()
public:
    USTMNeedAmmoDecorator();

protected:
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
private:

    
public:
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<ASTMBaseWeapon> WeaponType;
    
private:
};
