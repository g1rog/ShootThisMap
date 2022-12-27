
#pragma once

#include "CoreMinimal.h"
#include "STMCoreTypes.h"
#include "STMGameInstance.h"
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
	virtual void BeginPlay() override;
    virtual void OnPossess(APawn* InPawn) override;
    virtual void SetupInputComponent() override;
    
private:
    void OnPauseGame();
    void OnMatchStateChanged(ESTMMatchState State);
    void OnMuteSound();
    
public:
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USTMRespawnComponent> RespawnComponent;
    
};
