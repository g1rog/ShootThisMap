
#include "UI/STMGameHUD.h"
#include "Blueprint/UserWidget.h"

void ASTMGameHUD::BeginPlay()
{
    Super::BeginPlay();
    const auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
    if (PlayerHUDWidget)
        PlayerHUDWidget->AddToViewport();
}
