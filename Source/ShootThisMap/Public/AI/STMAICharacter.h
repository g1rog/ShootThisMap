
#pragma once

#include "CoreMinimal.h"
#include "Player/STMBaseCharacter.h"
#include "STMAICharacter.generated.h"

class UBehaviorTree;

UCLASS()
class SHOOTTHISMAP_API ASTMAICharacter : public ASTMBaseCharacter
{
	GENERATED_BODY()
    
public:
    ASTMAICharacter(const FObjectInitializer& ObjInit);
    virtual void Tick(const float DeltaTime) override;
    
protected:
private:

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    TObjectPtr<UBehaviorTree> BehaviorTreeAsset;
    
protected:
private:
    
	
};
