
#pragma once

#include "CoreMinimal.h"
#include "STMBaseWidget.h"
#include "STMCoreTypes.h"
#include "UI/STMBaseWidget.h"
#include "STMGameOverWidget.generated.h"

class UVerticalBox;
class UButton;

UCLASS()
class SHOOTTHISMAP_API USTMGameOverWidget : public USTMBaseWidget
{
	GENERATED_BODY()

protected:
    virtual void NativeOnInitialized() override;
    
private:
    UFUNCTION()
    void OnResetLevel();
    void OnMatchStateChanged(const ESTMMatchState State);
    void UpdatePlayersStat() const;
    
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVerticalBox> PlayerStatBox;

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> ResetLevelButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;
};
