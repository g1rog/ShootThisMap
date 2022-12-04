
#pragma once

#include "CoreMinimal.h"
#include "Weapon/STMBaseWeapon.h"
#include "STMRifleWeapon.generated.h"

class USTMWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

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
    FORCEINLINE TObjectPtr<AController> GetController() const;
    
    void MakeDamage(const FHitResult& HitResult);
    void InitMuzzleFX();
    void SetMuzzleFXVisibility(const bool Visible) const;
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd) const;

public:
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float DamageAmount = 20.0f;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    TObjectPtr<USTMWeaponFXComponent> WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TObjectPtr<UNiagaraSystem> TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

private:
    UPROPERTY()
    TObjectPtr<UNiagaraComponent> MuzzleFXComponent;
    FTimerHandle ShotTimerHandle;
};
