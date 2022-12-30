
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STMCharacterMovementComponent.generated.h"

UCLASS()
class SHOOTTHISMAP_API USTMCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
public:
    virtual float GetMaxSpeed() const override;
    
protected:
private:

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement", meta = (ClampMin = "1.5", ClampMax = "10.0"))
    float RunModifier = 2.0f;

protected:
private:
};
