
#include "Weapon/STMRifleWeapon.h"
#include "Weapon/Components/STMWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

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
    InitMuzzleFX();
   // GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::Printf(TEXT("Fire")));
    MakeShot();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTMRifleWeapon::MakeShot, TimeBetweenShots, true);
}

void ASTMRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetMuzzleFXVisibility(false);
}

void ASTMRifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty()) return;
    FVector TraceStart, TraceEnd;

    if (!GetTraceData(TraceStart, TraceEnd)) return;
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);
    
    FVector TraceFXEnd = TraceEnd;
    if (HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);
        WeaponFXComponent->PlayImpactFX(HitResult);
        //DrawDebugLine(GetWorld(), GetMuzzleSocketLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
        //GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Blue, FString::Printf(TEXT("%s"), *HitResult.BoneName.ToString()));
    }
    SpawnTraceFX(GetMuzzleSocketLocation(), TraceFXEnd);
    DecreaseAmmo();
}

void ASTMRifleWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor) return;
    DamagedActor->TakeDamage(DamageAmount, FDamageEvent{}, GetController(), this);
}

void ASTMRifleWeapon::InitMuzzleFX()
{
    if (!MuzzleFXComponent) MuzzleFXComponent = SpawnMuzzleFX();
    SetMuzzleFXVisibility(true);
}

void ASTMRifleWeapon::SetMuzzleFXVisibility(const bool Visible) const
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!Visible);
        MuzzleFXComponent->SetVisibility(Visible, true);
    }
}

void ASTMRifleWeapon::SpawnTraceFX(const FVector &TraceStart, const FVector &TraceEnd) const
{
    if (const auto TraceFXComponent =
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart))
            TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
}

FORCEINLINE TObjectPtr<AController> ASTMRifleWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}


