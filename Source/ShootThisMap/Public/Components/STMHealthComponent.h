
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STMCoreTypes.h"
#include "STMHealthComponent.generated.h"

class UCameraShakeBase;

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
    
    FORCEINLINE constexpr float GetHealth() const { return Health; }
    
    FORCEINLINE bool IsHealthFull () const;
    bool TryToAddHealth(const float HealthAmount);
    

protected:
	virtual void BeginPlay() override;
    
private:
    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamagedActor, const float Damage, const class UDamageType* DamageType,
        class AController* InstigatedBy, AActor* DamageCauser);

    void SetHealth(const float NewHealth);
    void HealUpdate();
    void PlayCameraShake() const;
    void Killed(const TObjectPtr<AController>& KillerController) const;

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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TSubclassOf<UCameraShakeBase> CameraShake;
    
private:
    FTimerHandle HealTimerHandle;
    float Health = 0.0f;
};
