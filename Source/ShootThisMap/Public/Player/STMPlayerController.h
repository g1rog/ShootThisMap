
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STMPlayerController.generated.h"

class USTMRespawnComponent;

UCLASS()
class SHOOTTHISMAP_API ASTMPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    ASTMPlayerController();
    
protected:
private:

public:
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USTMRespawnComponent> RespawnComponent;
    
};
