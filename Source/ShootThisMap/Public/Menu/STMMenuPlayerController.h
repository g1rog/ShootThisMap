
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STMMenuPlayerController.generated.h"

UCLASS()
class SHOOTTHISMAP_API ASTMMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    constexpr virtual void BeginPlay() override;
    
};
