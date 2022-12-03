
#include "Pickups/STMAmmoPickup.h"
#include "Components/STMHealthComponent.h"
#include "Components/STMWeaponComponent.h"
#include "STMUtils.h"

bool ASTMAmmoPickup::GivePickUpTo(const TObjectPtr<APawn> &PlayerPawn)
{
    const auto HealthComponent =
        STMUtils::GetSTMPlayerComponent<USTMHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;
    
    const auto WeaponComponent =
        STMUtils::GetSTMPlayerComponent<USTMWeaponComponent>(PlayerPawn);
    if (!WeaponComponent) return false;
    
    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);
}
