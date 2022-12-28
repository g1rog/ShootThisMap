
#pragma once

namespace 
{
	template <typename Type>
	concept NotifyClass = std::is_base_of_v<UAnimNotify, Type>;
}

class AnimUtils
{
public:
    template <NotifyClass Type>
    static constexpr auto FindNotifyByClass(const TObjectPtr<UAnimSequenceBase>& Animation)
		-> TObjectPtr<Type>
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
