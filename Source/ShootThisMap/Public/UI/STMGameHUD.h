
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STMCoreTypes.h"
#include "STMGameHUD.generated.h"

class USTMBaseWidget;

UCLASS()
class SHOOTTHISMAP_API ASTMGameHUD : public AHUD
{
    GENERATED_BODY()

public:
protected:
    virtual void BeginPlay() override;

private:
    void OnMatchStateChanged(ESTMMatchState State);
    
public:
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;
    
private:
    UPROPERTY()
    TMap<ESTMMatchState, TObjectPtr<USTMBaseWidget>> GameWidgets;

    UPROPERTY()
    TObjectPtr<USTMBaseWidget> CurrentWidget = nullptr;
};
