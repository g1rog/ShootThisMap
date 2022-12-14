
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;
class USTMWeaponFXComponent;

UCLASS()
class SHOOTTHISMAP_API ASTMProjectile : public AActor
{
    GENERATED_BODY()
	
public:	
    ASTMProjectile();
	void SetShotDirection(const FVector& Direction);
    
protected:
	virtual void BeginPlay() override;

private:
    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	TObjectPtr<AController> GetController() const;

public:
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    TObjectPtr<USphereComponent> CollisionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
    TObjectPtr<UProjectileMovementComponent> MovementComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "VFX")
    TObjectPtr<USTMWeaponFXComponent> WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageRadius = 300.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 50.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool DoFullDamage = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float LifeSeconds = 5.0f;
    
private:
    FVector ShotDirection;
};
