
#include "Pickups/STMBasePickup.h"
#include "Components/SphereComponent.h"

ASTMBasePickup::ASTMBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
    
}

void ASTMBasePickup::BeginPlay()
{
	Super::BeginPlay();
    
	GenerateRotationYaw();
}

void ASTMBasePickup::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));

}

void ASTMBasePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    const auto Pawn = Cast<APawn>(OtherActor);
    if (GivePickUpTo(Pawn))
        PickupWasTaken();
}

void ASTMBasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);
    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTMBasePickup::Respawn, RespawnTime);
}

void ASTMBasePickup::Respawn()
{
    GenerateRotationYaw();
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);
}

void ASTMBasePickup::GenerateRotationYaw()
{
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
    RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}

bool ASTMBasePickup::GivePickUpTo(const TObjectPtr<APawn> &PlayerPawn)
{
    return false;
}
