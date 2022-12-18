
#include "Menu/UI/STMLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"


void USTMLevelItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (LevelSelectButton)
        LevelSelectButton->OnClicked
            .AddDynamic(this, &USTMLevelItemWidget::OnLevelItemClicked);
}

void USTMLevelItemWidget::OnLevelItemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void USTMLevelItemWidget::SetSelected(const bool IsSelected)
{
   if (FrameImage)
       FrameImage->SetVisibility(IsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTMLevelItemWidget::SetLevelData(const FLevelData &Data)
{
    LevelData = Data;
    if (LevelNameTextBlock)
        LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
    if (LevelImage)
       LevelImage->SetBrushFromTexture(Data.LevelThumb);
}
