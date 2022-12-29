
#include "Menu/UI/STMLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void USTMLevelItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &USTMLevelItemWidget::OnLevelItemClicked);
        LevelSelectButton->OnHovered.AddDynamic(this, &USTMLevelItemWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &USTMLevelItemWidget::OnLevelItemUnhovered);
    }
}

void USTMLevelItemWidget::OnLevelItemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void USTMLevelItemWidget::SetLevelData(const FLevelData &Data)
{
    LevelData = Data;
    if (LevelNameTextBlock)
        LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
    if (LevelImage)
       LevelImage->SetBrushFromTexture(Data.LevelThumb);
}

void USTMLevelItemWidget::SetSelected(const bool IsSelected) const
{
    if (LevelImage)
        LevelImage->SetColorAndOpacity(IsSelected ? FColor::Red : FColor::White);
}

void USTMLevelItemWidget::OnLevelItemHovered()
{
    if (FrameImage)
        FrameImage->SetVisibility(ESlateVisibility::Visible);
}

void USTMLevelItemWidget::OnLevelItemUnhovered()
{
    if (FrameImage)
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
}


