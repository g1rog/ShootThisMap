
#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "STMAIPerceptionComponent.generated.h"

UCLASS()
class SHOOTTHISMAP_API USTMAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

public:
    TObjectPtr<AActor> GetClosestEnemy() const;
};
