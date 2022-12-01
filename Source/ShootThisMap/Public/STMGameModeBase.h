
#pragma once

#include "CoreMinimal.h"
#include "STMCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "STMGameModeBase.generated.h"

class AAIController;

UCLASS()
class SHOOTTHISMAP_API ASTMGameModeBase : public AGameModeBase
{
    GENERATED_BODY()
    
public:
    ASTMGameModeBase();
    virtual void StartPlay() override;
    virtual UClass* GetDefaultPawnClassForController_Implementation(AController *InController) override;
    
protected:
private:
    void SpawnBots();

public:
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;
    
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

private:
};
