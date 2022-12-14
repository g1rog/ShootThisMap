
#include "Menu/UI/STMMenuWidget.h"
#include "Menu/UI/STMLevelItemWidget.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Sound/SoundCue.h"
#include "STMGameInstance.h"

void USTMMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (StartGameButton)
        StartGameButton->OnClicked.AddDynamic(this, &USTMMenuWidget::OnStartGame);
    if (QuitGameButton)
        QuitGameButton->OnClicked.AddDynamic(this, &USTMMenuWidget::OnQuitGame);

    InitLevelItems();
}

void USTMMenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), StartGameSound);
}

void USTMMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation *Animation)
{
    if (Animation != HideAnimation) return;
    const auto GameInstance = GetSTMGameInstance();
    if (!GameInstance) return;
    UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelData().LevelName);
}

void USTMMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTMMenuWidget::InitLevelItems()
{
    const auto GameInstance = GetSTMGameInstance();
    if (!GameInstance) return;
    checkf(GameInstance->GetLevelsData().Num() != 0, TEXT("Level data is empty"));
	if (!LevelItemsBox) return;
	LevelItemsBox->ClearChildren();

    for (const auto& LevelData : GameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = 
            CreateWidget<USTMLevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget) continue;
        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &USTMMenuWidget::OnLevelSelected);
        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }
    if (GameInstance->GetStartupLevelData().LevelName.IsNone())
        OnLevelSelected(GameInstance->GetLevelsData()[0]);
    else
        OnLevelSelected(GameInstance->GetStartupLevelData());
}

void USTMMenuWidget::OnLevelSelected(const FLevelData &Data)
{
    const auto GameInstance = GetSTMGameInstance();
    if (!GameInstance) return;
    GameInstance->SetStartupLevel(Data);

    for (const auto& LevelItemWidget : LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

TObjectPtr<USTMGameInstance> USTMMenuWidget::GetSTMGameInstance() const
{
    return GetWorld() ?  GetWorld()->GetGameInstance<USTMGameInstance>() : nullptr;
}
