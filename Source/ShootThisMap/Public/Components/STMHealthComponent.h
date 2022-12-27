
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STMCoreTypes.h"
#include "STMHealthComponent.generated.h"

class UCameraShakeBase;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHISMAP_API USTMHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTMHealthComponent();

    UFUNCTION(BlueprintCallable)
    bool IsDead() const;

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const { return Health / MaxHealth; }
    
    float GetHealth() const { return Health; }
    bool IsHealthFull () const;
    
    bool TryToAddHealth(const float HealthAmount);

protected:
    virtual void BeginPlay() override;
    
private:
    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamagedActor, const float Damage, const class UDamageType* DamageType,
        class AController* InstigatedBy, AActor* DamageCauser);

    UFUNCTION()
    void OnTakePointDamage( AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation,
        class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection,
        const class UDamageType* DamageType, AActor* DamageCauser );

    UFUNCTION()
    void OnTakeRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin,
        FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);

    float GetPointDamageModifer(const TObjectPtr<AActor>& DamagedActor, const FName& BoneName);
    void ApplyDamage(float Damage, const TObjectPtr<AController>& InstigatedBy);
    void SetHealth(const float NewHealth);
    void HealUpdate();
    void PlayCameraShake() const;
    void Killed(const TObjectPtr<AController>& KillerController) const;
    void ReportDamageEvent(const float Damage, const TObjectPtr<AController>& InstigatedBy) const;
    
public:
    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;
    
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.0", ClampMax = "100.0"))
    float MaxHealth = 100.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "AutoHeal"))
    float HealUpdateTime = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "AutoHeal"))
    float HealDelay = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (EditCondition = "AutoHeal"))
    float HealModifier = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    bool AutoHeal = true;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
    TMap<TObjectPtr<UPhysicalMaterial>, float> DamageModifiers;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;
    
private:
    FTimerHandle HealTimerHandle;
    float Health = 0.0f;
};

