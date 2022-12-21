
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STMBaseWidget.generated.h"

UCLASS()
class SHOOTTHISMAP_API USTMBaseWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    FORCEINLINE virtual void Show();
    
protected:
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    TObjectPtr<UWidgetAnimation> ShowAnimation;
    
};
