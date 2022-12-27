
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STMBaseWidget.generated.h"

class USoundCue;

UCLASS()
class SHOOTTHISMAP_API USTMBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void Show();
    
protected:
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    TObjectPtr<UWidgetAnimation> ShowAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    TObjectPtr<USoundCue> OpenSound;
    
    
};
