
#pragma once

#include "CoreMinimal.h"
#include "STMCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STMGameOverWidget.generated.h"

class UVerticalBox;

UCLASS()
class SHOOTTHISMAP_API USTMGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual bool Initialize() override;

protected:
private:
    void OnMatchStateChanged(ESTMMatchState State);
    void UpdatePlayersStat();
    
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UVerticalBox> PlayerStatBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;
};
