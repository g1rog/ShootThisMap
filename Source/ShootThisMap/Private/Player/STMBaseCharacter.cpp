
#include "Player/STMBaseCharacter.h"
#include "Components/STMCharacterMovementComponent.h"
#include "Components/STMHealthComponent.h"
#include "GameFramework/Controller.h"
#include "Components/STMWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

ASTMBaseCharacter::ASTMBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTMCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

    HealthComponent = CreateDefaultSubobject<USTMHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<USTMWeaponComponent>("WeaponComponent");
}

void ASTMBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
    check(HealthComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &ASTMBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &ASTMBaseCharacter::OnHealthChanged);
}

void ASTMBaseCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
   // TakeDamage(0.3f, FDamageEvent{}, nullptr, this);
}

FORCEINLINE constexpr void ASTMBaseCharacter::SetPlayerColor(const FLinearColor& Color) const
{
    const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (!MaterialInstance) return;
    MaterialInstance->SetVectorParameterValue(MaterialColorName, Color);
}

bool ASTMBaseCharacter::IsRunning() const
{
    return false;
}

float ASTMBaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero()) return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees =  FMath::RadiansToDegrees(AngleBetween);
    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ASTMBaseCharacter::OnDeath()
{
    //PlayAnimMontage(DeathAnimMontage);
    GetCharacterMovement()->DisableMovement();
    WeaponComponent->StopFire();
    SetLifeSpan(5.0f);
    GetCapsuleComponent()->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
    WeaponComponent->Zoom(false);
}

void ASTMBaseCharacter::OnHealthChanged(const float Health, const float HealthDelta) const
{
    
}


