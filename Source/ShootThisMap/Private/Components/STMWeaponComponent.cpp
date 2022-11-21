
#include "Components/STMWeaponComponent.h"

#include "Animations/AnimUtils.h"
#include "Weapon/STMBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/STMEquipFinishedAnimNotify.h"
#include "Animations/STMReloadFinishedAnimNotify.h"

USTMWeaponComponent::USTMWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTMWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

    InitAnimations();

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

    for (const auto& i : WeaponData)
    {
        const auto Weapon = GetWorld()->SpawnActor<ASTMBaseWeapon>(i.WeaponClass);
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
    const auto CurrentWeaponData =
        WeaponData.FindByPredicate([&](const FWeaponData& Data) -> bool { return Data.WeaponClass == CurrentWeapon->GetClass(); });
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void USTMWeaponComponent::StartFire()
{
    if (!CanFire()) return;
    CurrentWeapon->StartFire();
}

void USTMWeaponComponent::StopFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->StopFire();
}

void USTMWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;
    CurrentWeaponId = (CurrentWeaponId + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponId);
}

void USTMWeaponComponent::PlayAnimMontage(const TObjectPtr<UAnimMontage> &Animation) const
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;
    Character->PlayAnimMontage(Animation);
    
}

void USTMWeaponComponent::InitAnimations()
{
    const auto EquipFinishedNotify = AnimUtils::FindNotifyByClass<USTMEquipFinishedAnimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify)
        EquipFinishedNotify->OnNotified.AddUObject(this, &USTMWeaponComponent::OnEquipFinished);
    else
        checkNoEntry();

    for (const auto& i : WeaponData)
    {
        const auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTMReloadFinishedAnimNotify>(i.ReloadAnimMontage);
        if (!ReloadFinishedNotify) continue;
        EquipFinishedNotify->OnNotified.AddUObject(this, &USTMWeaponComponent::OnReloadFinished);
    }
}

void USTMWeaponComponent::OnEquipFinished(const TObjectPtr<USkeletalMeshComponent> MeshComponent)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent) return;
    EquipAnimInProgress = false;
}

void USTMWeaponComponent::OnReloadFinished(const TObjectPtr<USkeletalMeshComponent> MeshComponent)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent) return;
    ReloadAnimInProgress = false;
}

bool USTMWeaponComponent::CanFire() const
{
   return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
    
}

bool USTMWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool USTMWeaponComponent::CanReload() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
    
}


void USTMWeaponComponent::Reload()
{
    if (!CanReload()) return;
    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}

bool USTMWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData &UIData) const
{
    if (CurrentWeapon)
    {
        UIData = CurrentWeapon->GetUIData();
        return true;
    }
    return false;
}

 bool USTMWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
 {
    if (CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetAmmoData();
        return true;
    }
    return false;
}



