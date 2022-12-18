
#pragma once

#include "CoreMinimal.h"
#include "STMCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STMMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class USTMGameInstance;
class USTMLevelItemWidget;

UCLASS()
class SHOOTTHISMAP_API USTMMenuWidget : public UUserWidget
{
    GENERATED_BODY()
    
protected:
    virtual void NativeOnInitialized() override;

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

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

private:
    UPROPERTY()
    TArray<TObjectPtr<USTMLevelItemWidget>> LevelItemWidgets;

};
