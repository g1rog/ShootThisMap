
#pragma once

#include "CoreMinimal.h"
#include "Weapon/STMBaseWeapon.h"
#include "STMRifleWeapon.generated.h"

class USTMWeaponFXComponent;

UCLASS()
class SHOOTTHISMAP_API ASTMRifleWeapon : public ASTMBaseWeapon
{
	GENERATED_BODY()

public:
    ASTMRifleWeapon();
    virtual void BeginPlay() override;
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    virtual void MakeShot() override;
private:
    void MakeDamage(const FHitResult& HitResult);

public:
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float DamageAmount = 20.0f;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    TObjectPtr<USTMWeaponFXComponent> WeaponFXComponent;
    
    
private:
    FTimerHandle ShotTimerHandle;
};
