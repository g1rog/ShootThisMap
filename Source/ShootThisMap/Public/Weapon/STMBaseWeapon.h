
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/STMWeaponComponent.h"
#include "STMCoreTypes.h"
#include "STMBaseWeapon.generated.h"

UCLASS()
class SHOOTTHISMAP_API ASTMBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTMBaseWeapon();
    virtual void StartFire();
    virtual void StopFire();

    FORCEINLINE FWeaponUIData GetUIData() const { return UIData; }
    FORCEINLINE FAmmoData GetAmmoData() const { return CurrentAmmo; }
protected:
	virtual void BeginPlay() override;

    virtual void MakeShot();
    void ChangeClip();
    void DecreaseAmmo();
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
    
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;
    
    TObjectPtr<APlayerController> GetPlayerController() const;
    FORCEINLINE FVector GetMuzzleSocketLocation() const;
private:

    
public:
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

private:
    FAmmoData CurrentAmmo;
    
};
