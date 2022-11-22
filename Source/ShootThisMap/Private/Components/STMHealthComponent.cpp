
#include "Components/STMHealthComponent.h"
#include "Engine/World.h"
#include "TimerManager.h"

USTMHealthComponent::USTMHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTMHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    check(MaxHealth > 0);
    
    SetHealth(MaxHealth);
    if (const TObjectPtr<AActor> ComponentOwner = GetOwner())
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTMHealthComponent::OnTakeAnyDamage);
}

CONSTEXPR FORCEINLINE float USTMHealthComponent::GetHealth() const { return Health; }

void USTMHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, const float Damage, const class UDamageType* DamageType,
      class AController* InstigatedBy, AActor* DamageCauser)
{
    if (FMath::IsNearlyEqual(Damage, 0.0f) || IsDead() || !GetWorld()) return;
    SetHealth(Health - Damage);
    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    
    if (IsDead())
        OnDeath.Broadcast();
    else if (AutoHeal && GetWorld())
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &USTMHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
}

bool USTMHealthComponent::IsDead() const
{
    return FMath::IsNearlyZero(Health);
}

void USTMHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);
    if (IsHealthFull() && GetWorld())
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
}

void USTMHealthComponent::SetHealth(const float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}

FORCEINLINE bool USTMHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

bool USTMHealthComponent::TryToAddHealth(const float HealthAmount)
{
    if (IsDead() || IsHealthFull()) return false;
    SetHealth(Health + HealthAmount);
    return true;
}


