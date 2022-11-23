
#include "Weapon/STMBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "Animations/AnimUtils.h"

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

    CurrentAmmo = DefaultAmmo;
}

void ASTMBaseWeapon::StartFire() {}

void ASTMBaseWeapon::StopFire() {}

void ASTMBaseWeapon::MakeShot() {}

TObjectPtr<APlayerController> ASTMBaseWeapon::GetPlayerController() const
{
    const TObjectPtr<ACharacter> Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;
    
    const TObjectPtr<APlayerController> Controller = Player->GetController<APlayerController>();
    return !Controller ? nullptr : Controller;
}

bool ASTMBaseWeapon::GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const
{
    const auto Controller = GetPlayerController();
    if (!Controller) return false;
    
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

FORCEINLINE FVector ASTMBaseWeapon::GetMuzzleSocketLocation() const
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
    if (CurrentAmmo.Bullets == 0)
        return;
    CurrentAmmo.Bullets--;
    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        StopFire();
        OnClipEmpty.Broadcast(this);
    }
}

FORCEINLINE bool ASTMBaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

FORCEINLINE bool ASTMBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

FORCEINLINE bool ASTMBaseWeapon::IsAmmoFull() const
{
    return CurrentAmmo.Clips == DefaultAmmo.Clips &&
           CurrentAmmo.Bullets == DefaultAmmo.Bullets;
}

void ASTMBaseWeapon::ChangeClip()
{
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    if (!CurrentAmmo.Infinite)
        CurrentAmmo.Clips--;
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

FORCEINLINE bool ASTMBaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}




