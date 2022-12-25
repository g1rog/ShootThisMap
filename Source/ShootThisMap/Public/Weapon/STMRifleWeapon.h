
#pragma once

#include "CoreMinimal.h"
#include "Weapon/STMBaseWeapon.h"
#include "STMRifleWeapon.generated.h"

class USTMWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;

UCLASS()
class SHOOTTHISMAP_API ASTMRifleWeapon : public ASTMBaseWeapon
{
    GENERATED_BODY()

public:
    ASTMRifleWeapon();
    virtual void BeginPlay() override;
    virtual void StartFire() override;
    virtual void StopFire() override;
    virtual void Zoom(bool Enabled) override;

protected:
    virtual void MakeShot() override;
    
private:
    FORCEINLINE TObjectPtr<AController> GetController() const;
    void MakeDamage(const FHitResult& HitResult);
    void InitFX();
    void SetFXActive(const bool IsActive) const;
    void SpawnTraceFX(const FVector& TraceStart, const FVector& TraceEnd) const;

public:
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 20.0f;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float FOVZoomAngle = 60.0f;

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    TObjectPtr<USTMWeaponFXComponent> WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TObjectPtr<UNiagaraSystem> TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

private:
    UPROPERTY()
    TObjectPtr<UNiagaraComponent> MuzzleFXComponent;

    UPROPERTY()
    TObjectPtr<UAudioComponent> FireAudioComponent;
    
    FTimerHandle ShotTimerHandle;

    float DefaultCameraFOV = 90.0f;
};
