
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STMPlayerState.generated.h"

UCLASS()
class SHOOTTHISMAP_API ASTMPlayerState : public APlayerState
{
    GENERATED_BODY()

public:
	void SetTeamID(int32 ID) { TeamID = ID; }
	void SetTeamColor(const FLinearColor& Color) {  TeamColor = Color; }
	FLinearColor GetTeamColor() const { return TeamColor; }
    
    int32 GetTeamID() const { return TeamID; }
    int32 GetKillsNum() const { return KillsNum; }
    int32 GetDeathsNum() const { return DeathsNum; }
    
    void AddKill() { ++KillsNum; }
    void AddDeath() { ++DeathsNum; }

protected:
private:

public:
protected:
private:
    int32 TeamID;
    FLinearColor TeamColor;
    int32 KillsNum = 0;
    int32 DeathsNum = 0;
};
