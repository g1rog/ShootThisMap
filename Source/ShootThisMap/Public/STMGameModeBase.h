
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
    virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause()) override;
    virtual bool ClearPause() override;
    
    void Killed(const TObjectPtr<AController>& KillerController, const TObjectPtr<AController>& VictimController);
    void RespawnRequest(const TObjectPtr<AController>& Controller);

    
    FORCEINLINE FGameData GetGameData() const { return GameData; }
    FORCEINLINE constexpr int32 GetCurrentRoundNum() const { return CurrentRound; }
    FORCEINLINE constexpr int32 GetRoundSecondsRemaining() const { return RoundCountDown; }

    
protected:
private:
    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();
    void ResetPlayers();
    void CreateTeamsInfo();
    void ResetOnePlayer(const TObjectPtr<AController>& Controller);
    void SetPlayerColor(const TObjectPtr<AController>& Controller) const;
    void StartRespawn(const TObjectPtr<AController>& Controller) const;
    void GameOver();
    void SetMatchState(ESTMMatchState State);
    FLinearColor SetColorByTeam(int32 TeamID) const;


public:
    FOnMatchStateChangedSignature OnMatchStateChanged;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;
    
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;


private:
    FTimerHandle GameRoundTimerHandle;
    int32 CurrentRound = 1;
    int32 RoundCountDown = 0;
    ESTMMatchState MatchState = ESTMMatchState::WaitingToStart;
    
};
