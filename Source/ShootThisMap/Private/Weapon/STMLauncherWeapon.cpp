
#include "Weapon/STMLauncherWeapon.h"
#include "Weapon/STMProjectile.h"
#include "Kismet/GameplayStatics.h"

void ASTMLauncherWeapon::StartFire()
{
    MakeShot();
}

void ASTMLauncherWeapon::MakeShot()
{
    if(!GetWorld()) return;
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleSocketLocation());
    const auto Projectile = UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), ProjectileClass, SpawnTransform);
    UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
    
}

