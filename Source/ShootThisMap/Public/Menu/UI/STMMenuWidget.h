
#pragma once

#include "CoreMinimal.h"
#include "STMCoreTypes.h"
#include "UI/STMBaseWidget.h"
#include "STMMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USTMGameInstance;
class USTMLevelItemWidget;
class USoundCue;

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

	TObjectPtr<USTMGameInstance> GetSTMGameInstance() const;

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& Data);
    
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> StartGameButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UHorizontalBox> LevelItemsBox;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    TObjectPtr<UWidgetAnimation> HideAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    TObjectPtr<USoundCue> StartGameSound;

private:
    UPROPERTY()
    TArray<TObjectPtr<USTMLevelItemWidget>> LevelItemWidgets;

};
