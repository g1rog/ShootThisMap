
#include "UI/STMPlayerHUDWidget.h"
#include "Components/STMHealthComponent.h"
#include "Components/STMWeaponComponent.h"
#include "STMUtils.h"

float USTMPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent = STMUtils::GetSTMPlayerComponent<USTMHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent) return 0.0f;
    return HealthComponent->GetHealthPercent();
}

bool USTMPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData &UIData) const
{
    const auto WeaponComponent = STMUtils::GetSTMPlayerComponent<USTMWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;
    return WeaponComponent->GetCurrentWeaponUIData(UIData);
}

bool USTMPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData &AmmoData) const
{
    const auto WeaponComponent = STMUtils::GetSTMPlayerComponent<USTMWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent) return false;
    return WeaponComponent->GetCurrentWeaponAmmoData(AmmoData);
}

bool USTMPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = STMUtils::GetSTMPlayerComponent<USTMHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool USTMPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}
