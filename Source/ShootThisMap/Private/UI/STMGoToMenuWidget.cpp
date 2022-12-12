
#include "UI/STMGoToMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STMGameInstance.h"

void USTMGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (GoToMenuButton)
        GoToMenuButton->OnClicked.AddDynamic(this, &USTMGoToMenuWidget::OnGoToMenu);
}

void USTMGoToMenuWidget::OnGoToMenu()
{
    if (!GetWorld()) return;
    const auto GameInstance = GetWorld()->GetGameInstance<USTMGameInstance>();

    if (!GameInstance) return;
    if (GameInstance->GetMenuLevelName().IsNone()) return;
    
    UGameplayStatics::OpenLevel(this, GameInstance->GetMenuLevelName());
}

