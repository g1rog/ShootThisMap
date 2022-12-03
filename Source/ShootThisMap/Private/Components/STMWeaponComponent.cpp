
#include "Components/STMWeaponComponent.h"
#include "Weapon/STMBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/STMEquipFinishedAnimNotify.h"
#include "Animations/STMReloadFinishedAnimNotify.h"
#include "Animations/AnimUtils.h"

USTMWeaponComponent::USTMWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTMWeaponComponent::BeginPlay()
{
	Super::BeginPlay();
    InitAnimations();
    SpawnWeapons();
    CurrentWeaponId = 0;
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

void USTMWeaponComponent::AttachWeaponToSocket(const TObjectPtr<ASTMBaseWeapon>& Weapon,
    const TObjectPtr<USceneComponent>& Mesh, const FName& SocketName)
{
    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(Mesh, AttachmentRules, SocketName);
}

void USTMWeaponComponent::EquipWeapon(const int32& WeaponId)
{
    const TObjectPtr<ACharacter> Character = Cast<ACharacter>(GetOwner());
    if (CurrentWeapon && Character)
    {
        StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }
    CurrentWeapon = Weapons[WeaponId];
    const auto CurrentWeaponData = WeaponData.FindByPredicate([&]<typename Type> (const Type& Data)
        constexpr -> bool { return Data.WeaponClass == CurrentWeapon->GetClass(); });

    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
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
    if (const auto EquipFinishedNotify =
        AnimUtils::FindNotifyByClass<USTMEquipFinishedAnimNotify>(EquipAnimMontage))
            EquipFinishedNotify->OnNotified.AddUObject(this, &USTMWeaponComponent::OnEquipFinished);
    else
        checkNoEntry();

    for (const auto& i : WeaponData)
    {
        const auto ReloadFinishedNotify = AnimUtils::FindNotifyByClass<USTMReloadFinishedAnimNotify>(i.ReloadAnimMontage);
        if (!ReloadFinishedNotify) checkNoEntry();
        ReloadFinishedNotify->OnNotified.AddUObject(this, &USTMWeaponComponent::OnReloadFinished);
    }
}

void USTMWeaponComponent::OnEquipFinished(const TObjectPtr<USkeletalMeshComponent> MeshComponent)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComponent != Character->GetMesh()) return;
    EquipAnimInProgress = false;
}

void USTMWeaponComponent::OnReloadFinished(const TObjectPtr<USkeletalMeshComponent> MeshComponent)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent) return;
    ReloadAnimInProgress = false;
}

FORCEINLINE bool USTMWeaponComponent::CanFire() const
{
   return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

FORCEINLINE bool USTMWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress && !ReloadAnimInProgress;
}

FORCEINLINE bool USTMWeaponComponent::CanReload() const
{
    return CurrentWeapon
            && !EquipAnimInProgress
            && !ReloadAnimInProgress
            && CurrentWeapon->CanReload();
}

FORCEINLINE void USTMWeaponComponent::Reload()
{
    ChangeClip();
}

void USTMWeaponComponent::OnClipEmpty(const TObjectPtr<ASTMBaseWeapon> AmmoEmptyWeapon)
{
    if (!AmmoEmptyWeapon) return;
    if (CurrentWeapon == AmmoEmptyWeapon)
    {
        ChangeClip();
    }
    else
    {
        for (const auto& Weapon : Weapons)
        {
            if (Weapon == AmmoEmptyWeapon)
                Weapon->ChangeClip();
        }
    }
}

void USTMWeaponComponent::ChangeClip()
{
    if (!CanReload()) return;
    CurrentWeapon->StopFire();
    CurrentWeapon->ChangeClip();
    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}

bool USTMWeaponComponent::TryToAddAmmo(TSubclassOf<ASTMBaseWeapon> WeaponType, int32 ClipsAmount)
{
    for (const auto& Weapon : Weapons)
        if (Weapon && Weapon->IsA(WeaponType))
            return Weapon->TryToAddAmmo(ClipsAmount);
    return false;
}

bool USTMWeaponComponent::NeedAmmo(TSubclassOf<ASTMBaseWeapon> WeaponType)
{
    for (const auto& Weapon : Weapons)
        if (Weapon && Weapon->IsA(WeaponType))
            return !Weapon->IsAmmoFull();
    return false;
}

bool USTMWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData &UIData) const
{
    if (!CurrentWeapon) return false;
    UIData = CurrentWeapon->GetUIData();
    return true;
}

bool USTMWeaponComponent::GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const
 {
    if (!CurrentWeapon) return false;
    AmmoData = CurrentWeapon->GetAmmoData();
    return true;
}



