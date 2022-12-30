
#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STMRespawnComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHISMAP_API USTMRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTMRespawnComponent();
    void Respawn(int32 RespawnTime);
    
    bool IsRespawnInProgress() const;
    int32 GetRespawnCountDown() const { return RespawnCountDown; }
    
protected:
private:
    void RespawnTimerUpdate();

public:
protected:
private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnCountDown;
};
