
#include "Menu/UI/STMMenuHUD.h"
#include "UI/STMBaseWidget.h"

void ASTMMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    if (const auto MenuWidget = CreateWidget<USTMBaseWidget>
        (GetWorld(), MenuWidgetClass))
    {
        MenuWidget->AddToViewport();
        MenuWidget->Show();
    }
}

