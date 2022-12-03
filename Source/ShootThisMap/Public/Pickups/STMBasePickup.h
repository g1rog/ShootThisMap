
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMBasePickup.generated.h"

class USphereComponent;

UCLASS()
class SHOOTTHISMAP_API ASTMBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTMBasePickup();
    virtual void Tick(const float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    virtual bool GivePickUpTo(const TObjectPtr<APawn>& PlayerPawn);
    
private:
    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();
    
public:
protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    TObjectPtr<USphereComponent> CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;
    
private:
    float RotationYaw = 0.0f;

};
