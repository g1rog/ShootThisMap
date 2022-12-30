
#include "Weapon/STMBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ASTMBaseWeapon::ASTMBaseWeapon()
{
    PrimaryActorTick.bCanEverTick = false;
    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void ASTMBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
    check(WeaponMesh);
	checkf(DefaultAmmo.Bullets > 0, TEXT("Bullets count couldn't be less or equal zero"));
	checkf(DefaultAmmo.Clips > 0, TEXT("Clips count couldn't be less or equal zero"));
    CurrentAmmo = DefaultAmmo;
}

void ASTMBaseWeapon::StartFire() { FireInProgress = true; }
void ASTMBaseWeapon::StopFire() { FireInProgress = false; }
void ASTMBaseWeapon::MakeShot() {}

bool ASTMBaseWeapon::GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const
{
    const auto STMCharacter = Cast<ACharacter>(GetOwner());
    if (!STMCharacter) return false;
    if (STMCharacter->IsPlayerControlled())
    {
        const auto Controller = STMCharacter->GetController<APlayerController>();
        if (!Controller) return false;
        Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    }
    else
    {
        ViewLocation = GetMuzzleSocketLocation();
        ViewRotation = WeaponMesh->GetSocketRotation(MuzzleSocketName);
    }
    return true;
}

FVector ASTMBaseWeapon::GetMuzzleSocketLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

bool ASTMBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;
    const FVector TraceDirection = ViewRotation.Vector(); 
    TraceStart = ViewLocation;
    TraceEnd = TraceStart + TraceDirection * TraceMaxDistance;
    return true;
}

void ASTMBaseWeapon::MakeHit(FHitResult &HitResult, const FVector &TraceStart, const FVector &TraceEnd) const
{
    if (!GetWorld()) return;
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());
    CollisionParams.bReturnPhysicalMaterial = true;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
}

void ASTMBaseWeapon::DecreaseAmmo()
{
    if (CurrentAmmo.Bullets == 0) return;
    CurrentAmmo.Bullets--;
    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        StopFire();
        OnClipEmpty.Broadcast(this);
    }
}

bool ASTMBaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

bool ASTMBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

bool ASTMBaseWeapon::IsAmmoFull() const
{
    return CurrentAmmo.Clips == DefaultAmmo.Clips &&
           CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

void ASTMBaseWeapon::ChangeClip()
{
	if (!CurrentAmmo.Infinite)
	{
		if (CurrentAmmo.Clips == 0) return;
		CurrentAmmo.Clips--;
	}
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
}

bool ASTMBaseWeapon::TryToAddAmmo(int32 ClipsAmount)
{
    if (CurrentAmmo.Infinite || IsAmmoFull() || ClipsAmount <= 0) return false;
    if (IsAmmoEmpty())
    {
        CurrentAmmo.Clips = FMath::Clamp(ClipsAmount, 0, DefaultAmmo.Clips + 1);
        OnClipEmpty.Broadcast(this);
    }
    else if (CurrentAmmo.Clips < DefaultAmmo.Clips)
    {
        const auto NextClipsAmount = CurrentAmmo.Clips + ClipsAmount;
        if (DefaultAmmo.Clips - NextClipsAmount >= 0 )
        {
            CurrentAmmo.Clips = NextClipsAmount;
        }
        else
        {
            CurrentAmmo.Clips = DefaultAmmo.Clips;
            CurrentAmmo.Bullets = DefaultAmmo.Bullets;
        }
    }
    else
    {
        CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    }
    return true;
}

bool ASTMBaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

UNiagaraComponent* ASTMBaseWeapon::SpawnMuzzleFX() const
{
    return UNiagaraFunctionLibrary::SpawnSystemAttached(MuzzleFX, WeaponMesh, MuzzleSocketName,
        FVector::ZeroVector, FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
}




