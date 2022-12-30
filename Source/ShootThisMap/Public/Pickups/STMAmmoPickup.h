
#pragma once

#include "CoreMinimal.h"
#include "Pickups/STMBasePickup.h"
#include "STMAmmoPickup.generated.h"

class ASTMBaseWeapon;

UCLASS()
class SHOOTTHISMAP_API ASTMAmmoPickup : public ASTMBasePickup
{
	GENERATED_BODY()
	
public:
protected:
    virtual bool GivePickUpTo(const TObjectPtr<APawn>& PlayerPawn) override;

private:
public:
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    int32 ClipsAmount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<ASTMBaseWeapon> WeaponType;

private:
};
