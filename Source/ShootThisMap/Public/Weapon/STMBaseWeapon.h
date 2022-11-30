
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMCoreTypes.h"
#include "STMBaseWeapon.generated.h"

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class SHOOTTHISMAP_API ASTMBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTMBaseWeapon();
    
    virtual void StartFire();
    virtual void StopFire();
    void ChangeClip();
    bool TryToAddAmmo(int32 ClipsAmount);
    FORCEINLINE bool IsAmmoEmpty() const;
    FORCEINLINE bool CanReload() const;
    FORCEINLINE bool IsAmmoFull() const;
    FORCEINLINE FWeaponUIData GetUIData() const { return UIData; }
    FORCEINLINE FAmmoData GetAmmoData() const { return CurrentAmmo; }

    
protected:
	virtual void BeginPlay() override;

    virtual void MakeShot();
    void DecreaseAmmo();
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
    
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

    FORCEINLINE bool IsClipEmpty() const;
    FORCEINLINE FVector GetMuzzleSocketLocation() const;
    
    TObjectPtr<APlayerController> GetPlayerController() const;
    TObjectPtr<UNiagaraComponent> SpawnMuzzleFX();

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

private:
    FAmmoData CurrentAmmo;
    
};
