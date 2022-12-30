
#include "Components/STMCharacterMovementComponent.h"
#include "Player/STMBaseCharacter.h"

float USTMCharacterMovementComponent::GetMaxSpeed() const 
{
    const float MaxSpeed = Super::GetMaxSpeed();
	const TObjectPtr<ASTMBaseCharacter> Player = Cast<ASTMBaseCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
