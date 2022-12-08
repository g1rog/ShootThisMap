
#include "UI/STMPlayerHUDWidget.h"
#include "Components/STMHealthComponent.h"
#include "Components/STMWeaponComponent.h"
#include "STMUtils.h"

float USTMPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent =
        STMUtils::GetSTMPlayerComponent<USTMHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent ? HealthComponent->GetHealthPercent() : 0.0f;
}

bool USTMPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData &UIData) const
{
    const auto WeaponComponent =
        STMUtils::GetSTMPlayerComponent<USTMWeaponComponent>(GetOwningPlayerPawn());
    return WeaponComponent ? WeaponComponent->GetCurrentWeaponUIData(UIData) : false;
}

bool USTMPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData &AmmoData) const
{
    const auto WeaponComponent =
        STMUtils::GetSTMPlayerComponent<USTMWeaponComponent>(GetOwningPlayerPawn());
    return WeaponComponent ? WeaponComponent->GetCurrentWeaponAmmoData(AmmoData) : false;
}

bool USTMPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent =
        STMUtils::GetSTMPlayerComponent<USTMHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool USTMPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer(); 
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool USTMPlayerHUDWidget::Initialize()
{
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTMPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
    return Super::Initialize();
}

void USTMPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComponent =
        STMUtils::GetSTMPlayerComponent<USTMHealthComponent>(NewPawn);
    if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
            HealthComponent->OnHealthChanged.AddUObject(this, &USTMPlayerHUDWidget::OnHealthChanged);
}

FORCEINLINE void USTMPlayerHUDWidget::OnHealthChanged(const float Health, const float HealthDelta)
{
    if (HealthDelta < 0.0f) OnTakeDamage();
}

