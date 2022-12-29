
#pragma once

#include "CoreMinimal.h"
#include "Weapon/STMBaseWeapon.h"
#include "STMLauncherWeapon.generated.h"

class ASTMProjectile;
class USoundCue;

UCLASS()
class SHOOTTHISMAP_API ASTMLauncherWeapon : public ASTMBaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;

protected:
    virtual void MakeShot() override;
    
public:
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTMProjectile> ProjectileClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    TObjectPtr<USoundCue> NoAmmoSound;
	
};
