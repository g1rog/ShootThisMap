
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STMGoToMenuWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHISMAP_API USTMGoToMenuWidget : public UUserWidget
{
	GENERATED_BODY()
    
protected:
    virtual void NativeOnInitialized() override;

private:
    UFUNCTION()
    void OnGoToMenu();
    
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> GoToMenuButton;
    
};
