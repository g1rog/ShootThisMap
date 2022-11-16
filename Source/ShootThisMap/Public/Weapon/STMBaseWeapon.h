
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMBaseWeapon.generated.h"

UCLASS()
class SHOOTTHISMAP_API ASTMBaseWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTMBaseWeapon();
    virtual void StartFire();
    virtual void StopFire();

protected:
	virtual void BeginPlay() override;
    virtual void MakeShot();
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;
    bool GetPlayerViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;
    void MakeHit(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd) const;
    TObjectPtr<APlayerController> GetPlayerController() const;
    FORCEINLINE FVector GetMuzzleSocketLocation() const;

private:

public:
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TObjectPtr<USkeletalMeshComponent> WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TraceMaxDistance = 1000.0f;

private:
};
