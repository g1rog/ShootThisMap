
#include "Menu/UI/STMMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ASTMMenuHUD::BeginPlay()
{
    Super::BeginPlay();
    if (const auto MenuWidget = CreateWidget<UUserWidget>
        (GetWorld(), MenuWidgetClass))
    {
        MenuWidget->AddToViewport();
    }
        
}

