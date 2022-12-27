﻿#pragma once

#include "Player/STMPlayerState.h"

namespace STMComponentConcept
{
	template <typename ComponentType>
	concept STMComponent = std::is_base_of_v<UActorComponent, ComponentType>
	|| requires(ComponentType Type) {{ ComponentType::StaticClass() }
		-> std::convertible_to<UClass*>;};;
}

class STMUtils
{
public:
    template <STMComponentConcept::STMComponent ComponentType>
	//template <typename ComponentType>
    static auto GetSTMPlayerComponent(const TObjectPtr<AActor>& PlayerPawn)
		-> TObjectPtr<ComponentType>
    {
        if (!PlayerPawn) return nullptr;
        const auto Component = PlayerPawn->GetComponentByClass(ComponentType::StaticClass());
        return Component ? Cast<ComponentType>(Component) : nullptr;  
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
    
    static FText TextFromInt(const int32 Number) { return FText::AsNumber(Number); }
};
