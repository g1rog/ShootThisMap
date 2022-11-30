
#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "STMEnemyEnvQueryContext.generated.h"

UCLASS()
class SHOOTTHISMAP_API USTMEnemyEnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
public:
    virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;
protected:
private:

public:
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName EnemyActorKeyName = "EnemyActor";
};
