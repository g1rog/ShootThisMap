
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STMAIController.generated.h"

UCLASS()
class SHOOTTHISMAP_API ASTMAIController : public AAIController
{
	GENERATED_BODY()
public:
protected:
    virtual void OnPossess(APawn* InPawn) override;
    
private:
    
	
};