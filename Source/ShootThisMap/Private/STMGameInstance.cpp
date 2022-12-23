
#include "STMGameInstance.h"
#include "Sound/STMSoundFuncLib.h"

FORCEINLINE void USTMGameInstance::ToggleVolume() const
{
    USTMSoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}

