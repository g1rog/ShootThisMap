
#pragma once

#include "CoreMinimal.h"
#include "Weapon/STMBaseWeapon.h"
#include "STMLauncherWeapon.generated.h"

class ASTMProjectile;

UCLASS()
class SHOOTTHISMAP_API ASTMLauncherWeapon : public ASTMBaseWeapon
{
	GENERATED_BODY()

public:
    virtual void StartFire() override;

protected:
    virtual void MakeShot() override;
    
private:

public:
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTMProjectile> ProjectileClass;
    
private:
    
    
	
};
