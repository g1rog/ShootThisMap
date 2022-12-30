
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMCoreTypes.h"
#include "NiagaraComponent.h"
#include "STMBaseWeapon.generated.h"

class USkeletalMeshComponent;
class USoundCue;

UCLASS()
class SHOOTTHISMAP_API ASTMBaseWeapon : public AActor
{
    GENERATED_BODY()
	
public:	
    ASTMBaseWeapon();
    virtual void StartFire();
    virtual void StopFire();
    virtual void Zoom(bool Enabled) {}
    void ChangeClip();
    bool TryToAddAmmo(int32 ClipsAmount);
	bool IsAmmoEmpty() const;
	bool CanReload() const;
	bool IsAmmoFull() const;
	bool IsFiring() const { return FireInProgress; }
	auto GetUIData() const { return UIData; }
	auto GetAmmoData() const { return CurrentAmmo; }

protected:
    virtual void BeginPlay() override;
    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
    void DecreaseAmmo();
    
    UNiagaraComponent* SpawnMuzzleFX() const;

	bool IsClipEmpty() const;
    FVector GetMuzzleSocketLocation() const;
    
private:
public:
    FOnClipEmptySignature OnClipEmpty;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TObjectPtr<USkeletalMeshComponent> WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 1000.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{15,10, false};
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TObjectPtr<UNiagaraSystem> MuzzleFX;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    TObjectPtr<USoundCue> FireSound;

	bool FireInProgress = false;

private:
    FAmmoData CurrentAmmo;
};
