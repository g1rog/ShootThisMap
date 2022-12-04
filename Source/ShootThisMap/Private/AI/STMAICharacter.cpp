
#include "AI/STMAICharacter.h"
#include "AI/STMAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/STMAIWeaponComponent.h"
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
}

void ASTMAICharacter::BeginPlay() 
{
    Super::BeginPlay();
}

void ASTMAICharacter::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);
}

void ASTMAICharacter::OnDeath() 
{
    Super::OnDeath();
    const auto STMController = Cast<AAIController>(Controller);
    if (STMController && STMController->BrainComponent)
        STMController->BrainComponent->Cleanup();
}
