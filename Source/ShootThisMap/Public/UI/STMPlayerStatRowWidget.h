
#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STMPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class SHOOTTHISMAP_API USTMPlayerStatRowWidget : public UUserWidget
{
	GENERATED_BODY()
    
public:
    FORCEINLINE void SetPlayerName(const FText& Text) const;
    FORCEINLINE void SetKills(const FText& Text) const;
    FORCEINLINE void SetDeaths(const FText& Text) const;
    FORCEINLINE void SetTeam(const FText& Text) const;
    FORCEINLINE void SetPlayerIndicatorVisibility(const bool Visible) const;
    
protected:
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> PlayerNameTextBlock;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> KillsTextBlock;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> DeathsTextBlock;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UTextBlock> TeamTextBlock;
    
    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> PlayerIndicatorImage;
    
    
};
