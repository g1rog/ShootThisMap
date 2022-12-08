
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STMCoreTypes.h"
#include "STMWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHISMAP_API USTMWeaponFXComponent : public UActorComponent
{
    GENERATED_BODY()

public:	
    USTMWeaponFXComponent();
    void PlayImpactFX(const FHitResult& Hit);
    
protected:
private:	
public:
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FImpactData DefaultImpactData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    TMap<TObjectPtr<UPhysicalMaterial>, FImpactData> ImpactDataMap;
    
private:
    
		
};
