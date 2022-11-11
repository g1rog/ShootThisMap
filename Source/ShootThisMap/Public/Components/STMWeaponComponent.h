
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STMWeaponComponent.generated.h"

class ASTMBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHISMAP_API USTMWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTMWeaponComponent();

    void Fire();
    
protected:
	virtual void BeginPlay() override;

private:
    void SpawnWeapon();


public:
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ASTMBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponAttachPointName = "WeaponSocket";
    
private:
    UPROPERTY()
    TObjectPtr<ASTMBaseWeapon> CurrentWeapon = nullptr;
    
		
};
