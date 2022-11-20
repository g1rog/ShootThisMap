
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STMWeaponComponent.generated.h"

class ASTMBaseWeapon;
class UAnimMontage;

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTMBaseWeapon> WeaponClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TObjectPtr<UAnimMontage> ReloadAnimMontage;
};

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
    void OnReloadFinished(const TObjectPtr<USkeletalMeshComponent> MeshComponent);

    bool CanFire() const;
    bool CanEquip() const;
    bool CanReload() const;

    template <typename Type> static Type* FindNotifyByClass(const TObjectPtr<UAnimSequenceBase>& Animation)
    {
        if (!Animation) return nullptr;
        const auto NotifyEvents = Animation->Notifies;
        for (const auto& i : NotifyEvents)
        {
            if (const auto AnimNotify = Cast<Type>(i.Notify))
                return AnimNotify;
        }
        return nullptr;
    }

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
    TArray<ASTMBaseWeapon*> Weapons;
    int32 CurrentWeaponId = 0;
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;
		
};
