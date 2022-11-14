
#include "Weapon/STMProjectile.h"
#include "Components/SphereComponent.h"

ASTMProjectile::ASTMProjectile()
{
	PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    SetRootComponent(CollisionComponent);
    
}

void ASTMProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

