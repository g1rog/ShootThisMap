
#include "Animations/STMEquipFinishedAnimNotify.h"

void USTMEquipFinishedAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
    
}
