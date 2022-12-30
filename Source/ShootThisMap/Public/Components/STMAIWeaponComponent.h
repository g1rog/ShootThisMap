
#pragma once

#include "CoreMinimal.h"
#include "Components/STMWeaponComponent.h"
#include "STMAIWeaponComponent.generated.h"

UCLASS()
class SHOOTTHISMAP_API USTMAIWeaponComponent : public USTMWeaponComponent
{
	GENERATED_BODY()
	
public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
