
#include "AI/STMAICharacter.h"
#include "AI/STMAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

ASTMAICharacter::ASTMAICharacter(const FObjectInitializer& ObjInit)
    : Super(ObjInit)
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

void ASTMAICharacter::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}
