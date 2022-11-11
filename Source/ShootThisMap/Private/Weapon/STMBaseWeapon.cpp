
#include "Weapon/STMBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"

ASTMBaseWeapon::ASTMBaseWeapon()
{
	PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASTMBaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASTMBaseWeapon::Fire()
{
    GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::Printf(TEXT("Fire")));
}

