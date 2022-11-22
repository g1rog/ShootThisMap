#pragma once

#include "STMCoreTypes.generated.h"

class ASTMBaseWeapon;

DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, const TObjectPtr<ASTMBaseWeapon>&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float);


USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
    int32 Clips;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool Infinite;
};

USTRUCT(BlueprintType)
struct FWeaponData
{

    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ASTMBaseWeapon> WeaponClass;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TObjectPtr<UAnimMontage> ReloadAnimMontage;
};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TObjectPtr<UTexture2D> MainIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TObjectPtr<UTexture2D> CrossHairIcon;
};
