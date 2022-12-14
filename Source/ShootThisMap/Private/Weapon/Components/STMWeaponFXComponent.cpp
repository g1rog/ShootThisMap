
#include "Weapon/Components/STMWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"

USTMWeaponFXComponent::USTMWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void USTMWeaponFXComponent::PlayImpactFX(const FHitResult &Hit)
{
    auto ImpactData = DefaultImpactData;
    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
            ImpactData = ImpactDataMap[PhysMat];
    }
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),
        ImpactData.NiagaraEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
    
    if (const auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),ImpactData.DecalData.Material,
        ImpactData.DecalData.Size, Hit.ImpactPoint, Hit.ImpactNormal.Rotation()))
            DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
}

