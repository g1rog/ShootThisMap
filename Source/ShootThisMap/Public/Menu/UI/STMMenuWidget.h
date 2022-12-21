
#pragma once

#include "CoreMinimal.h"
#include "STMCoreTypes.h"
#include "UI/STMBaseWidget.h"
#include "STMMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USTMGameInstance;
class USTMLevelItemWidget;

UCLASS()
class SHOOTTHISMAP_API USTMMenuWidget : public USTMBaseWidget
{
    GENERATED_BODY()
    
protected:
    virtual void NativeOnInitialized() override;
    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation *Animation) override;

private:
    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();

    FORCEINLINE TObjectPtr<USTMGameInstance> GetSTMGameInstance() const;

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& Data);
    
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> StartGameButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UHorizontalBox> LevelItemsBox;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    TObjectPtr<UWidgetAnimation> HideAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    

private:
    UPROPERTY()
    TArray<TObjectPtr<USTMLevelItemWidget>> LevelItemWidgets;

};
