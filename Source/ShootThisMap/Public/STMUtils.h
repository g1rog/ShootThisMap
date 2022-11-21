#pragma once

class STMUtils
{
public:
    template <typename Type>
    static Type* GetSTMPlayerComponent(APawn* PlayerPawn)
    {
        if (!PlayerPawn) return nullptr;
        const auto Component = PlayerPawn->GetComponentByClass(Type::StaticClass());
        return Cast<Type>(Component);  
    }
};
