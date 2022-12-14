
#include "Weapon/STMProjectile.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/STMWeaponFXComponent.h"

ASTMProjectile::ASTMProjectile()
{
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);
    
    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->InitialSpeed = 2000.0f;
    WeaponFXComponent = CreateDefaultSubobject<USTMWeaponFXComponent>("WeaponFXComponent");
}

void ASTMProjectile::BeginPlay()
{
    Super::BeginPlay();
    check(MovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);
    
    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;
    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &ASTMProjectile::OnProjectileHit);
    SetLifeSpan(LifeSeconds);
}

void ASTMProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld()) return;
    MovementComponent->StopMovementImmediately();
    UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(),
        DamageRadius, UDamageType::StaticClass(), {GetOwner()}, this, GetController(), DoFullDamage);
    WeaponFXComponent->PlayImpactFX(Hit);
    Destroy();
}
void ASTMProjectile::SetShotDirection(const FVector& Direction)
{
    ShotDirection = Direction;
}

TObjectPtr<AController> ASTMProjectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}

