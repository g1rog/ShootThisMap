
#include "Weapon/STMBaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

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
	
}

void ASTMBaseWeapon::StartFire()
{
    GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Red, FString::Printf(TEXT("Fire")));
    MakeShot();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &ASTMBaseWeapon::MakeShot, TimeBetweenShots, true);
    
}

void ASTMBaseWeapon::StopFire()
{
   GetWorldTimerManager().ClearTimer(ShotTimerHandle);
}

void ASTMBaseWeapon::MakeShot()
{
    if (!GetWorld()) return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;
    
    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    if (HitResult.bBlockingHit)
    {
        MakeDamage(HitResult);
        DrawDebugLine(GetWorld(), GetMuzzleSocketLocation(), HitResult.ImpactPoint, FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24, FColor::Red, false, 5.0f);
        GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Blue, FString::Printf(TEXT("%s"), *HitResult.BoneName.ToString()));
    }
    else
    {
        DrawDebugLine(GetWorld(), GetMuzzleSocketLocation(), TraceEnd, FColor::Red, false, 3.0f, 0, 3.0f);
    }
}

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
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility);
}

void ASTMBaseWeapon::MakeDamage(const FHitResult& HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor) return;
    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(), this);
}


