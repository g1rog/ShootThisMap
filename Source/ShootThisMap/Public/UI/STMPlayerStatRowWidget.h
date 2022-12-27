
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
	void SetPlayerName(const FText& Text) const;
	void SetKills(const FText& Text) const;
	void SetDeaths(const FText& Text) const;
	void SetTeam(const FText& Text) const;
	void SetTeamColor(const FLinearColor& Color) const;
	void SetPlayerIndicatorVisibility(const bool Visible) const;
    
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

    UPROPERTY(meta = (BindWidget))
    TObjectPtr<UImage> TeamImage;
};
