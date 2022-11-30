
#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STMAIController.generated.h"

class USTMAIPerceptionComponent;

UCLASS()
class SHOOTTHISMAP_API ASTMAIController : public AAIController
{
	GENERATED_BODY()
public:
    ASTMAIController();
    
protected:
    virtual void OnPossess(APawn* InPawn) override;
    virtual void Tick(float DeltaTime) override;
private:

public:
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USTMAIPerceptionComponent> STMAIPerceptionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    FName FocusOnKeyName = "EnemyActor";

private:
    TObjectPtr<AActor> GetFocusOnActor() const;
};
