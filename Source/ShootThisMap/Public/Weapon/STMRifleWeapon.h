
#pragma once

#include "CoreMinimal.h"
#include "Weapon/STMBaseWeapon.h"
#include "STMRifleWeapon.generated.h"

UCLASS()
class SHOOTTHISMAP_API ASTMRifleWeapon : public ASTMBaseWeapon
{
	GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    virtual void MakeShot() override;
private:

public:
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TimeBetweenShots = 0.1f;
    
private:
    FTimerHandle ShotTimerHandle;
};
