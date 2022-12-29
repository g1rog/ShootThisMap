
#include "Weapon/STMLauncherWeapon.h"
#include "Weapon/STMProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void ASTMLauncherWeapon::StartFire()
{
	Super::StartFire();
    MakeShot();
}

void ASTMLauncherWeapon::MakeShot()
{
    if (!GetWorld()) return;
    if (IsAmmoEmpty())
    {
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());
        return;
    }
    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleSocketLocation()).GetSafeNormal();
    const FTransform SpawnTransform(FRotator::ZeroRotator, GetMuzzleSocketLocation());
    if (const auto Projectile =
        GetWorld()->SpawnActorDeferred<ASTMProjectile>(ProjectileClass, SpawnTransform))
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }
    DecreaseAmmo();
    SpawnMuzzleFX();
    UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
	StopFire();
}

