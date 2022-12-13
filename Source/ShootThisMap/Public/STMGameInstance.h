
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STMGameInstance.generated.h"

UCLASS()
class SHOOTTHISMAP_API USTMGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    FName GetStartupLevelName() const { return StartUpLevelName; }
    FName GetMenuLevelName() const { return MenuLevelName; }

    
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName StartUpLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;

    
};
