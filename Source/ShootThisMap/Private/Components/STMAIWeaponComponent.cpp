
#include "Components/STMAIWeaponComponent.h"
#include "Weapon/STMBaseWeapon.h"

void USTMAIWeaponComponent::StartFire()
{
    if (!CanFire()) return;
    if (CurrentWeapon->IsAmmoEmpty())
        NextWeapon();
    else
        CurrentWeapon->StartFire();
}

void USTMAIWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;
    int32 NextIndex = (CurrentWeaponId + 1) % Weapons.Num();
    while (NextIndex!=CurrentWeaponId)
    {
        if (!Weapons[NextIndex]->IsAmmoEmpty()) break;
        NextIndex = (NextIndex + 1) % Weapons.Num();
    }
    if (CurrentWeaponId != NextIndex)
    {
        CurrentWeaponId = NextIndex;
        EquipWeapon(CurrentWeaponId);
    }
    
}
