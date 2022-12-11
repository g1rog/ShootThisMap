
#include "UI/STMPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

bool USTMPauseWidget::Initialize()
{
   const auto InitStatus = Super::Initialize();
   if (ClearPauseButton)
       ClearPauseButton->OnClicked.AddDynamic(this, &USTMPauseWidget::OnClearPause);
   return InitStatus; 
}

void USTMPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;
    GetWorld()->GetAuthGameMode()->ClearPause();
}
