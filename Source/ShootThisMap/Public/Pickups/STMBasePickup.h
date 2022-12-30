
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STMBasePickup.generated.h"

class USphereComponent;
class USoundCue;

UCLASS()
class SHOOTTHISMAP_API ASTMBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	ASTMBasePickup();
    virtual void Tick(const float DeltaTime) override;
	bool CouldBeTaken() const;

protected:
	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
    virtual bool GivePickUpTo(const TObjectPtr<APawn>& PlayerPawn);
    
private:
    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();
    
public:
protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
    TObjectPtr<USphereComponent> CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    TObjectPtr<USoundCue> PickupTakenSound;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;
    
private:
	UPROPERTY()
	TArray<TObjectPtr<APawn>> OverlappingPawns;

	FTimerHandle RespawnTimerHandle;
    float RotationYaw = 0.0f;
};
