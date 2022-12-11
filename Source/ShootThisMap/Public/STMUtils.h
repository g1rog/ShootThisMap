#pragma once

#include "Player/STMPlayerState.h"

class STMUtils
{
public:
    template <typename ComponentType>
    static constexpr TObjectPtr<ComponentType> GetSTMPlayerComponent(const TObjectPtr<AActor>& PlayerPawn)
    {
        if (!PlayerPawn) return nullptr;
        const auto Component = PlayerPawn->GetComponentByClass(ComponentType::StaticClass());
        return Cast<ComponentType>(Component);  
    }
    
    static bool AreEnemies(const TObjectPtr<AController>& FirstController,
                           const TObjectPtr<AController>& SecondController)
    {
        if (!FirstController || !SecondController || FirstController == SecondController) return false;
        const auto FirstPlayerState = Cast<ASTMPlayerState>(FirstController->PlayerState);
        const auto SecondPlayerState = Cast<ASTMPlayerState>(SecondController->PlayerState);

        return FirstPlayerState && SecondPlayerState &&
            FirstPlayerState->GetTeamID() != SecondPlayerState->GetTeamID();
    }
    
    static FText TextFromInt(const int32 Number)
    {
        return FText::FromString(FString::FromInt(Number));
    }
};
