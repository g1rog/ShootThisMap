
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

    SpawnWeapon();
}

void USTMWeaponComponent::SpawnWeapon() 
{
    if (!GetWorld()) return;

    const auto Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;
    
    CurrentWeapon = GetWorld()->SpawnActor<ASTMBaseWeapon>(WeaponClass);
    if (!CurrentWeapon) return;
    
    const FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(Character->GetMesh(), AttachmentRules, WeaponAttachPointName);
    
}

void USTMWeaponComponent::Fire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->Fire();
}
