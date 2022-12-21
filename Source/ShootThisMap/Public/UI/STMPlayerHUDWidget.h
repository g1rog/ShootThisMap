
#pragma once

#include "CoreMinimal.h"
#include "STMBaseWidget.h"
#include "UI/STMBaseWidget.h"
#include "STMPlayerHUDWidget.generated.h"

class UProgressBar;
class UWidgetAnimation;

UCLASS()
class SHOOTTHISMAP_API USTMPlayerHUDWidget : public USTMBaseWidget
{
    GENERATED_BODY()
    
public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeaponAmmoData(FAmmoData& AmmoData) const;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetKillsNum() const;
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    FString FormatBullets(const int32 BulletsNum) const;
    
protected:
    virtual void NativeOnInitialized() override;

private:
    FORCEINLINE void OnHealthChanged(const float Health, const float HealthDelta);
    void OnNewPawn(APawn* NewPawn);
    void UpdateHealthBar() const;

public:
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UProgressBar> HealthProgressBar;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    TObjectPtr<UWidgetAnimation> DamageAnimation;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor GoodColor = FColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor BadColor = FColor::Red;
    
private:
};
