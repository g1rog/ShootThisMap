
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
    FORCEINLINE static constexpr auto FindNotifyByClass(const TObjectPtr<UAnimSequenceBase>& Animation)
		-> TObjectPtr<Type>
    {
        if (!Animation) return nullptr;
        for (const auto& NotifyEvent : Animation->Notifies)
        {
            if (const auto AnimNotify = Cast<Type>(NotifyEvent.Notify))
                return AnimNotify;
        }
        return nullptr;
    }
};
