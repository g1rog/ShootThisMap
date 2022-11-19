
#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STMEquipFinishedAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, TObjectPtr<USkeletalMeshComponent>);

UCLASS()
class SHOOTTHISMAP_API USTMEquipFinishedAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
    
protected:
private:

public:
    FOnNotifiedSignature OnNotified;
    
protected:
private:

};
