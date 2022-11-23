
#include "Weapon/STMRifleWeapon.h"
#include "Weapon/Components/STMWeaponFXComponent.h"

ASTMRifleWeapon::ASTMRifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<USTMWeaponFXComponent>("WeaponFXComponent");
}

void ASTMRifleWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponFXComponent);
}

void ASTMRifleWeapon::StartFire()
{
    GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::Printf(TEXT("Fire")));
    MakeShot();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTMRifleWeapon::MakeShot, TimeBetweenShots, true);
    
}

void ASTMRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTMRifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty()) return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;
    
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit)
    {
        MakeDamage(HitResult);
        WeaponFXComponent->PlayImpactFX(HitResult);
        //DrawDebugLine(GetWorld(), GetMuzzleSocketLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
        //GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Blue, FString::Printf(TEXT("%s"), *HitResult.BoneName.ToString()));
    }
    else
    {
        WeaponFXComponent->PlayImpactFX(HitResult);
       // DrawDebugLine(GetWorld(), GetMuzzleSocketLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    }
    DecreaseAmmo();
}

void ASTMRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor) return;
    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}