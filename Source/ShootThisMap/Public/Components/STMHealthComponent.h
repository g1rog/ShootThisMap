
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STMHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHISMAP_API USTMHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTMHealthComponent();

    UFUNCTION(BlueprintCallable)
    bool IsDead() const;
    
    CONSTEXPR FORCEINLINE float GetHealth() const;

protected:
	virtual void BeginPlay() override;
    
private:
    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamagedActor, const float Damage, const class UDamageType* DamageType,
        class AController* InstigatedBy, AActor* DamageCauser);

    void SetHealth(const float NewHealth);
    void HealUpdate();

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
    
private:
    FTimerHandle HealTimerHandle;
    float Health = 0.0f;
};
