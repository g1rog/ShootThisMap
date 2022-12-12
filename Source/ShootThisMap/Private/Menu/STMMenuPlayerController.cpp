
#include "Menu/STMMenuPlayerController.h"

constexpr void ASTMMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;
}
