
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
    void MakeDamage(const FHitResult& HitResult);
    FORCEINLINE FVector GetMuzzleSocketLocation() const;
    TObjectPtr<APlayerController> GetPlayerController() const;

private:

public:
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    TObjectPtr<USkeletalMeshComponent> WeaponMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 1000.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float DamageAmount = 20.0f;

private:
    
};
