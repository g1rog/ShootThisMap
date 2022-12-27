
#pragma once

class AnimUtils
{
public:
    template <typename Type>
    static TObjectPtr<Type> FindNotifyByClass(const TObjectPtr<UAnimSequenceBase>& Animation)
    {
        if (!Animation) return nullptr;
        const auto NotifyEvents = Animation->Notifies;
        for (const auto& NotifyEvent : NotifyEvents)
        {
            if (const auto AnimNotify = Cast<Type>(NotifyEvent.Notify))
                return AnimNotify;
        }
        return nullptr;
    }
};
