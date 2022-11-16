
#include "Components/STMWeaponComponent.h"
#include "Weapon/STMBaseWeapon.h"
#include "GameFramework/Character.h"

USTMWeaponComponent::USTMWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTMWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    CurrentWeaponId = 0;
    SpawnWeapons();
    EquipWeapon(CurrentWeaponId);
}

void USTMWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (const auto& Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);

}

void USTMWeaponComponent::SpawnWeapons() 
{
    const TObjectPtr<ACharacter> Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld()) return;

    for (const auto& WeaponClass : WeaponClasses)
    {
        const auto Weapon = GetWorld()->SpawnActor<ASTMBaseWeapon>(WeaponClass);
        if (!Weapon) return;
        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);
        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void USTMWeaponComponent::AttachWeaponToSocket(const TObjectPtr<ASTMBaseWeapon>& Weapon, const TObjectPtr<USceneComponent>& Mesh, const FName& SocketName)
{
    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(Mesh, AttachmentRules, SocketName);
}

void USTMWeaponComponent::EquipWeapon(const int32 WeaponId)
{
    const TObjectPtr<ACharacter> Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    if (CurrentWeapon)
    {
        StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponId];
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
}

void USTMWeaponComponent::StartFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StartFire();
}

void USTMWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void USTMWeaponComponent::NextWeapon()
{
    CurrentWeaponId = (CurrentWeaponId + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponId);
}


