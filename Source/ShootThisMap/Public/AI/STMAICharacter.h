
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
protected:
private:

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    TObjectPtr<UBehaviorTree> BehaviorTreeAsset;
    
protected:
   

    
private:
    
	
};
