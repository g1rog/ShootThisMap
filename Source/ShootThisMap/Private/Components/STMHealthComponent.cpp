
#include "Components/STMHealthComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Camera/CameraShakeBase.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Perception/AISense_Damage.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "STMGameModeBase.h"

USTMHealthComponent::USTMHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void USTMHealthComponent::BeginPlay()
{
	Super::BeginPlay();
    check(MaxHealth > 0);
    
    SetHealth(MaxHealth);
    if (const TObjectPtr<AActor> ComponentOwner = GetOwner())
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &USTMHealthComponent::OnTakeAnyDamage);
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &USTMHealthComponent::OnTakePointDamage);
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &USTMHealthComponent::OnTakeRadialDamage);

    }
}

void USTMHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, const float Damage, const class UDamageType* DamageType,
      class AController* InstigatedBy, AActor* DamageCauser) {}

void USTMHealthComponent::OnTakePointDamage(AActor *DamagedActor, float Damage, AController *InstigatedBy,
    FVector HitLocation, UPrimitiveComponent *FHitComponent, FName BoneName, FVector ShotFromDirection,
    const UDamageType *DamageType, AActor *DamageCauser)
{
    const auto FinalDamage = Damage * GetPointDamageModifer(DamagedActor, BoneName);
    ApplyDamage(FinalDamage, InstigatedBy);  
}

void USTMHealthComponent::OnTakeRadialDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
    FVector Origin, FHitResult HitInfo, AController *InstigatedBy, AActor *DamageCauser)
{
    ApplyDamage(Damage, InstigatedBy);  
}

float USTMHealthComponent::GetPointDamageModifer(const TObjectPtr<AActor> &DamagedActor,
    const FName &BoneName)
{
    const auto Character = Cast<ACharacter>(DamagedActor);
    if (!Character ||
        !Character->GetMesh() ||
        !Character->GetMesh()->GetBodyInstance(BoneName))
            return 1.0f;
    
    const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();
    return PhysMaterial || DamageModifiers.Contains(PhysMaterial) ? DamageModifiers[PhysMaterial] : 1.0f;
}

void USTMHealthComponent::ApplyDamage(float Damage, const TObjectPtr<AController> &InstigatedBy)
{
    if (FMath::IsNearlyEqual(Damage, 0.0f) || IsDead() || !GetWorld()) return;
    SetHealth(Health - Damage);
    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    
    if (IsDead())
    {
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if (AutoHeal && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this,
            &USTMHealthComponent::HealUpdate, HealUpdateTime, true, HealDelay);
    }
    PlayCameraShake();
    ReportDamageEvent(Damage, InstigatedBy);
}

bool USTMHealthComponent::IsDead() const
{
    return FMath::IsNearlyZero(Health);
}

void USTMHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);
    if (IsHealthFull() && GetWorld()) GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
}

void USTMHealthComponent::SetHealth(const float NewHealth)
{
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;
    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
}

bool USTMHealthComponent::IsHealthFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

bool USTMHealthComponent::TryToAddHealth(const float HealthAmount)
{
    if (IsDead() || IsHealthFull()) return false;
    SetHealth(Health + HealthAmount);
    return true;
}

void USTMHealthComponent::PlayCameraShake() const
{
    if (IsDead()) return;
    if (const auto Player = Cast<APawn>(GetOwner()))
    {
        const auto Controller = Player->GetController<APlayerController>();
        if (!Controller || !Controller->PlayerCameraManager) return;
        Controller->PlayerCameraManager->StartCameraShake(CameraShake);
    }
}

void USTMHealthComponent::Killed(const TObjectPtr<AController> &KillerController) const
{
    if (!GetWorld()) return;
    const auto GameMode = Cast<ASTMGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode) return;
    const auto Player = Cast<APawn>(GetOwner());
    const auto VictimController = Player ? Player->Controller : nullptr;
    GameMode->Killed(KillerController, VictimController);
}

void USTMHealthComponent::ReportDamageEvent(const float Damage, const TObjectPtr<AController> &InstigatedBy) const
{
    if (!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner()) return;
    UAISense_Damage::ReportDamageEvent(GetWorld(), GetOwner(),
        InstigatedBy->GetPawn(), Damage,
        InstigatedBy->GetPawn()->GetActorLocation(),
        GetOwner()->GetActorLocation());
}

