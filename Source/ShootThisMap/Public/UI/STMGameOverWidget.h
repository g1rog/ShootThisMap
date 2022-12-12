
#pragma once

#include "CoreMinimal.h"
#include "STMCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STMGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTTHISMAP_API USTMGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;
    
private:
    UFUNCTION()
    void OnResetLevel();
    void OnMatchStateChanged(ESTMMatchState State);
    void UpdatePlayersStat() const;
    
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVerticalBox> PlayerStatBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> ResetLevelButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;
};
