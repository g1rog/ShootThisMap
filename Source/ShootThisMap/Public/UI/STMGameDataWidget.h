
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STMGameDataWidget.generated.h"

class ASTMGameModeBase;
class ASTMPlayerState;

UCLASS()
class SHOOTTHISMAP_API USTMGameDataWidget : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetKillsNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetCurrentRoundNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetTotalRoundsNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetRoundSecondsRemaining() const;

protected:
private:
    FORCEINLINE TObjectPtr<ASTMGameModeBase> GetSTMGameMode() const;
    FORCEINLINE TObjectPtr<ASTMPlayerState> GetSTMPlayerState() const;
    
};
