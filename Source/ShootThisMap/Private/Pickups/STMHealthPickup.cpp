
#include "Pickups/STMHealthPickup.h"
#include "Components/STMHealthComponent.h"
#include "STMUtils.h"

bool ASTMHealthPickup::GivePickUpTo(const TObjectPtr<APawn> &PlayerPawn)
{
    const auto HealthComponent = STMUtils::GetSTMPlayerComponent<USTMHealthComponent>(PlayerPawn);
    if (!HealthComponent) return false;
    return HealthComponent->TryToAddHealth(HealthAmount);
}
