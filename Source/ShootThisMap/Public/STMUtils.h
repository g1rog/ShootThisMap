#pragma once

class STMUtils
{
public:
    template <typename Type>
    static TObjectPtr<Type> GetSTMPlayerComponent(const TObjectPtr<AActor>& PlayerPawn)
    {
        if (!PlayerPawn) return nullptr;
        const auto Component = PlayerPawn->GetComponentByClass(Type::StaticClass());
        return Cast<Type>(Component);  
    }
};
