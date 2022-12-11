
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STMPauseWidget.generated.h"

class UButton;

UCLASS()
class SHOOTTHISMAP_API USTMPauseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    virtual bool Initialize() override;

protected:
private:
    UFUNCTION()
    void OnClearPause();
    
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UButton> ClearPauseButton;
    
};
