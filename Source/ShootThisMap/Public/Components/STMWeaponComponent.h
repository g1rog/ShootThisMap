
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

    void StartFire();
    void StopFire();
    void NextWeapon();
    
protected:
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    void SpawnWeapons();
    void AttachWeaponToSocket(const TObjectPtr<ASTMBaseWeapon>& Weapon, const TObjectPtr<USceneComponent>& SceneComponent, const FName& SocketName);
    void EquipWeapon(int32 WeaponId);
    void PlayAnimMontage(const TObjectPtr<UAnimMontage>& Animation) const;
    void InitAnimations();
    void OnEquipFinished(const TObjectPtr<USkeletalMeshComponent> MeshComponent);
    bool CanFire() const;
    bool CanEquip() const;
public:
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<ASTMBaseWeapon>> WeaponClasses;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> EquipAnimMontage;
    
private:
    TObjectPtr<ASTMBaseWeapon> CurrentWeapon = nullptr;
    TArray<ASTMBaseWeapon*> Weapons;
    int32 CurrentWeaponId = 0;
    bool EquipAnimInProgress = false;
		
};
