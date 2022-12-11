
#pragma once

class AnimUtils
{
public:
    template <typename Type>
    static constexpr TObjectPtr<Type> FindNotifyByClass(const TObjectPtr<UAnimSequenceBase>& Animation)
    {
        if (!Animation) return nullptr;
        const auto NotifyEvents = Animation->Notifies;
        for (const auto& i : NotifyEvents)
        {
            if (const auto AnimNotify = Cast<Type>(i.Notify))
                return AnimNotify;
        }
        return nullptr;
    }
};
