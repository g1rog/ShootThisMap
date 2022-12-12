
#include "UI/STMPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

void USTMPauseWidget::NativeOnInitialized()
{
   Super::NativeOnInitialized();
   if (ClearPauseButton)
       ClearPauseButton->OnClicked.AddDynamic(this, &USTMPauseWidget::OnClearPause);
}

void USTMPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    GetWorld()->GetAuthGameMode()->ClearPause();
}
