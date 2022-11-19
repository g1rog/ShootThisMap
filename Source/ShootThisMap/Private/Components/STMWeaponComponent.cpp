
#include "Components/STMWeaponComponent.h"
#include "Weapon/STMBaseWeapon.h"
#include "GameFramework/Character.h"
#include "Animations/STMEquipFinishedAnimNotify.h"

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
    if (!EquipAnimMontage) return;
    const auto NotifyEvents = EquipAnimMontage->Notifies;
    for (const auto& i : NotifyEvents)
    {
        const auto EquipFinishedNotify = Cast<USTMEquipFinishedAnimNotify>(i.Notify);
        if (EquipFinishedNotify) EquipFinishedNotify->OnNotified.AddUObject(this, &USTMWeaponComponent::OnEquipFinished);
        break;
    }
}

void USTMWeaponComponent::OnEquipFinished(const TObjectPtr<USkeletalMeshComponent> MeshComponent)
{
    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent) return;
    EquipAnimInProgress = false;
}

bool USTMWeaponComponent::CanFire() const
{
   return CurrentWeapon && !EquipAnimInProgress;
    
}

bool USTMWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress;
}



