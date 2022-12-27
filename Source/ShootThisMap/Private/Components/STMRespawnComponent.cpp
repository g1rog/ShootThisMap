
#include "Components/STMRespawnComponent.h"
#include "STMGameModeBase.h"

USTMRespawnComponent::USTMRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTMRespawnComponent::Respawn(int32 RespawnTime)
{
    if (!GetWorld()) return;
    RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USTMRespawnComponent::RespawnTimerUpdate, 1.0f, true);
    
}

void USTMRespawnComponent::RespawnTimerUpdate()
{
    if (--RespawnCountDown == 0)
    {
        if (!GetWorld()) return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
        const auto GameMode = Cast<ASTMGameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode) return;
        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}

bool USTMRespawnComponent::IsRespawnInProgress() const
{
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}


