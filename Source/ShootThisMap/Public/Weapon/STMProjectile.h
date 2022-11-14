
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMProjectile.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHISMAP_API ASTMProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTMProjectile();

protected:
	virtual void BeginPlay() override;

private:

public:
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TObjectPtr<USphereComponent> CollisionComponent;
    
private:
    

};
