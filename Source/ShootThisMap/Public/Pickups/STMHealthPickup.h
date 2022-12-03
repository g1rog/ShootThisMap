
#pragma once

#include "CoreMinimal.h"
#include "Pickups/STMBasePickup.h"
#include "STMHealthPickup.generated.h"

UCLASS()
class SHOOTTHISMAP_API ASTMHealthPickup : public ASTMBasePickup
{
	GENERATED_BODY()

public:
protected:
    virtual bool GivePickUpTo(const TObjectPtr<APawn>& PlayerPawn) override;

private:
public:
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    float HealthAmount = 100.0f;
    
private:
    
	
};
