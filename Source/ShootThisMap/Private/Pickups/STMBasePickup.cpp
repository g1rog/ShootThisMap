
#include "Pickups/STMBasePickup.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

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
    check(CollisionComponent);
	GenerateRotationYaw();
}

void ASTMBasePickup::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));
	
	for (const auto& OverlapPawn : OverlappingPawns)
	{
		if (GivePickUpTo(OverlapPawn))
		{
			PickupWasTaken();
			break;
		}
	}
}

bool ASTMBasePickup::CouldBeTaken() const
{
	return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
}

void ASTMBasePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);
    const auto Pawn = Cast<APawn>(OtherActor);
    if (GivePickUpTo(Pawn))
        PickupWasTaken();
	else if (Pawn)
		OverlappingPawns.Add(Pawn);
}

void ASTMBasePickup::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	const auto Pawn = Cast<APawn>(OtherActor);
	OverlappingPawns.Remove(Pawn);
}

void ASTMBasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
	if (GetRootComponent())	
		GetRootComponent()->SetVisibility(false, true);
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTMBasePickup::Respawn, RespawnTime);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), PickupTakenSound, GetActorLocation());
}

void ASTMBasePickup::Respawn()
{
    GenerateRotationYaw();
	if (GetRootComponent())
		GetRootComponent()->SetVisibility(true, true);
	CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
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
