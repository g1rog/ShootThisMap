
#include "AI/STMAICharacter.h"
#include "AI/STMAIController.h"
#include "UI/STMHealthBarWidget.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STMAIWeaponComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/STMHealthComponent.h"
#include "BrainComponent.h"

ASTMAICharacter::ASTMAICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit.SetDefaultSubobjectClass<USTMAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ASTMAIController::StaticClass();
    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASTMAICharacter::BeginPlay() 
{
    Super::BeginPlay();
    check(HealthWidgetComponent);
}

void ASTMAICharacter::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
    UpdateHealthWidgetVisibility();
}

void ASTMAICharacter::OnDeath() 
{
    Super::OnDeath();
    const auto STMController = Cast<AAIController>(Controller);
    if (STMController && STMController->BrainComponent)
        STMController->BrainComponent->Cleanup();
}

void ASTMAICharacter::OnHealthChanged(const float Health, const float HealthDelta) const
{
    Super::OnHealthChanged(Health, HealthDelta);
    const auto HealthBarWidget = Cast<USTMHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (!HealthBarWidget) return;
    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}
void ASTMAICharacter::UpdateHealthWidgetVisibility() const
{
    if (!GetWorld() ||
        !GetWorld()->GetFirstPlayerController() ||
        !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
        return;
            
    const auto PlayerLocation = GetWorld()
        ->GetFirstPlayerController()
        ->GetPawnOrSpectator()
        ->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation, GetActorLocation());
    HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}
