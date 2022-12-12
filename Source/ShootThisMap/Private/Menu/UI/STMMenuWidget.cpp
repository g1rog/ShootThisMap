
#include "Menu/UI/STMMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "STMGameInstance.h"

void USTMMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (StartGameButton)
        StartGameButton->OnClicked.AddDynamic(this, &USTMMenuWidget::OnStartGame);
    if (QuitGameButton)
        QuitGameButton->OnClicked.AddDynamic(this, &USTMMenuWidget::OnQuitGame);
}

void USTMMenuWidget::OnStartGame()
{
    if (!GetWorld()) return;
    const auto GameInstance = GetWorld()->GetGameInstance<USTMGameInstance>();

    if (!GameInstance) return;
    if (GameInstance->GetStartupLevelName().IsNone()) return;
    
    UGameplayStatics::OpenLevel(this, GameInstance->GetStartupLevelName());
}

void USTMMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
