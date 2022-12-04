
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STMPlayerState.generated.h"

UCLASS()
class SHOOTTHISMAP_API ASTMPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
    FORCEINLINE constexpr void SetTeamID(int32 ID) { TeamID = ID; }
    FORCEINLINE constexpr void SetTeamColor(const FLinearColor& Color) {  TeamColor = Color; }

    FORCEINLINE constexpr int32 GetTeamID() const { return TeamID; }
    FORCEINLINE constexpr FLinearColor GetTeamColor() const { return TeamColor; }

    
protected:
private:

public:
protected:
private:
    int32 TeamID;
    FLinearColor TeamColor;
};
