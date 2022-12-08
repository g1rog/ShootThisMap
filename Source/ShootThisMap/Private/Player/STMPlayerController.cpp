
#include "Player/STMPlayerController.h"
#include "Components/STMRespawnComponent.h"

ASTMPlayerController::ASTMPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<USTMRespawnComponent>("RespawnComponent");
}
