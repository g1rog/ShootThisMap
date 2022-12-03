#pragma once

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
};
