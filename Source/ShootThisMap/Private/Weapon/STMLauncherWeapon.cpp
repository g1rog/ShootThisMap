
#include "Weapon/STMLauncherWeapon.h"
#include "Weapon/STMProjectile.h"

void ASTMLauncherWeapon::StartFire()
{
    MakeShot();
}

void ASTMLauncherWeapon::MakeShot()
{
    if(!GetWorld() || IsAmmoEmpty()) return;
    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleSocketLocation()).GetSafeNormal();
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleSocketLocation());
    const auto Projectile = GetWorld()->SpawnActorDeferred<ASTMProjectile>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
    DecreaseAmmo();
    SpawnMuzzleFX();
}

