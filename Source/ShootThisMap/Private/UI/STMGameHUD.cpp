
#include "UI/STMGameHUD.h"
#include "Blueprint/UserWidget.h"

void ASTMGameHUD::BeginPlay()
{
    Super::BeginPlay();
    if (const auto PlayerHUDWidget =
        CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass))
            PlayerHUDWidget->AddToViewport();
}
