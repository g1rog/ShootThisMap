
#include "STMGameInstance.h"
#include "Sound/STMSoundFuncLib.h"

void USTMGameInstance::ToggleVolume() const
{
    USTMSoundFuncLib::ToggleSoundClassVolume(MasterSoundClass);
}

