
#include "Weapon/Components/STMWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

USTMWeaponFXComponent::USTMWeaponFXComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USTMWeaponFXComponent::PlayImpactFX(const FHitResult &Hit)
{
    auto Effect = DefaultEffect;
    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (EffectsMap.Contains(PhysMat))
        {
            Effect = EffectsMap[PhysMat];
        }
    }
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
}

