
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STMCoreTypes.h"
#include "STMWeaponComponent.generated.h"

class ASTMBaseWeapon;
class UAnimMontage;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHISMAP_API USTMWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

    USTMWeaponComponent();
    void StartFire();
    void StopFire();
    void NextWeapon();
    void Reload();
    void OnClipEmpty(const TObjectPtr<ASTMBaseWeapon> AmmoEmptyWeapon);
    void ChangeClip();
    bool TryToAddAmmo(TSubclassOf<ASTMBaseWeapon> WeaponType, int32 ClipsAmount);
    FORCEINLINE bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    FORCEINLINE bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

protected:
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
    void SpawnWeapons();
    void AttachWeaponToSocket(const TObjectPtr<ASTMBaseWeapon>& Weapon, const TObjectPtr<USceneComponent>& SceneComponent, const FName& SocketName);
    void EquipWeapon(const int32& WeaponId);
    void PlayAnimMontage(const TObjectPtr<UAnimMontage>& Animation) const;
    void InitAnimations();
    void OnEquipFinished(const TObjectPtr<USkeletalMeshComponent> MeshComponent);
    void OnReloadFinished(const TObjectPtr<USkeletalMeshComponent> MeshComponent);

    bool CanFire() const;
    bool CanEquip() const;
    bool CanReload() const;

  

public:
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    TObjectPtr<UAnimMontage> EquipAnimMontage;
    
private:
    UPROPERTY()
    TObjectPtr<UAnimMontage> CurrentReloadAnimMontage = nullptr;
    TObjectPtr<ASTMBaseWeapon> CurrentWeapon = nullptr;
    TArray<TObjectPtr<ASTMBaseWeapon>> Weapons;
    int32 CurrentWeaponId = 0;
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;
		
};
