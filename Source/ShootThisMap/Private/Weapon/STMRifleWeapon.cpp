
#include "Weapon/STMRifleWeapon.h"
#include "Weapon/Components/STMWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"
#include "Components/AudioComponent.h"

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
	Super::StartFire();
    InitFX();
   // GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::Printf(TEXT("Fire")));
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTMRifleWeapon::MakeShot, TimeBetweenShots, true);
	MakeShot();
}

void ASTMRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetFXActive(false);
}

void ASTMRifleWeapon::Zoom(const bool Enabled)
{
    Super::Zoom(Enabled);
    const auto Controller = Cast<APlayerController>(GetController());
    if (!Controller || !Controller->PlayerCameraManager) return;
    if (Enabled)
        DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
    Controller->PlayerCameraManager->SetFOV(Enabled ? FOVZoomAngle : DefaultCameraFOV);
}

void ASTMRifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
	    StopFire();
    	return;
    }
	
    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
	    StopFire();
    	return;
    }
	
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
    
    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = HitResult;
    DamagedActor->TakeDamage(DamageAmount, PointDamageEvent, GetController(), this);
}

void ASTMRifleWeapon::InitFX()
{
    if (!MuzzleFXComponent)
        MuzzleFXComponent = SpawnMuzzleFX();
    if (!FireAudioComponent)
        FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound,WeaponMesh, MuzzleSocketName);

    SetFXActive(true);
}

void ASTMRifleWeapon::SetFXActive(const bool IsActive) const
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!IsActive);
        MuzzleFXComponent->SetVisibility(IsActive, true);
    }
    if (FireAudioComponent)
        IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
}

void ASTMRifleWeapon::SpawnTraceFX(const FVector &TraceStart, const FVector &TraceEnd) const
{
    if (const auto TraceFXComponent =
        UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart))
            TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
}

TObjectPtr<AController> ASTMRifleWeapon::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}


