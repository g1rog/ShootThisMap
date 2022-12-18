
#pragma once

#include "CoreMinimal.h"
#include "STMCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "STMLevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;

UCLASS()
class SHOOTTHISMAP_API USTMLevelItemWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	FORCEINLINE auto GetLevelData() const { return LevelData; }
	FORCEINLINE void SetSelected(const bool IsSelected);

    void SetLevelData(const FLevelData& Data);

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnLevelItemClicked();

public:
    FOnLevelSelectedSignature OnLevelSelected;

protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> LevelSelectButton;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> LevelNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> FrameImage;

    UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> LevelImage = nullptr;
    
private:
	FLevelData LevelData;
	
};
