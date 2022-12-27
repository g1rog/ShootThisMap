
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
    virtual void StartFire();
    virtual void StopFire();
    virtual void NextWeapon();
    void OnClipEmpty(const TObjectPtr<ASTMBaseWeapon> AmmoEmptyWeapon);
    void ChangeClip();
    void Zoom(bool Enabled);
    bool TryToAddAmmo(TSubclassOf<ASTMBaseWeapon> WeaponType, int32 ClipsAmount);
    bool NeedAmmo(TSubclassOf<ASTMBaseWeapon> WeaponType);

    void Reload();
    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;

protected:
	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    void EquipWeapon(const int32& WeaponId);

    bool CanFire() const;
    bool CanEquip() const;
    
private:
    void SpawnWeapons();
    void AttachWeaponToSocket(const TObjectPtr<ASTMBaseWeapon>& Weapon,
        const TObjectPtr<USceneComponent>& SceneComponent, const FName& SocketName);
    void PlayAnimMontage(const TObjectPtr<UAnimMontage>& Animation) const;
    void InitAnimations();
    void OnEquipFinished(const TObjectPtr<USkeletalMeshComponent> MeshComponent);
    void OnReloadFinished(const TObjectPtr<USkeletalMeshComponent> MeshComponent);
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

    UPROPERTY()
    TObjectPtr<ASTMBaseWeapon> CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<TObjectPtr<ASTMBaseWeapon>> Weapons;

    int32 CurrentWeaponId = 0;
    
private:
    UPROPERTY()
    TObjectPtr<UAnimMontage> CurrentReloadAnimMontage = nullptr;
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;
		
};
