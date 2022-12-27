
#include "UI/STMPlayerHUDWidget.h"
#include "Components/STMHealthComponent.h"
#include "Components/STMWeaponComponent.h"
#include "Components/ProgressBar.h"
#include "Player/STMPlayerState.h"
#include "STMUtils.h"

float USTMPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent =
        STMUtils::GetSTMPlayerComponent<USTMHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent ? HealthComponent->GetHealthPercent() : 0.0f;
}

bool USTMPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData &UIData) const
{
    const auto WeaponComponent =
        STMUtils::GetSTMPlayerComponent<USTMWeaponComponent>(GetOwningPlayerPawn());
    return WeaponComponent ? WeaponComponent->GetCurrentWeaponUIData(UIData) : false;
}

bool USTMPlayerHUDWidget::GetCurrentWeaponAmmoData(FAmmoData &AmmoData) const
{
    const auto WeaponComponent =
        STMUtils::GetSTMPlayerComponent<USTMWeaponComponent>(GetOwningPlayerPawn());
    return WeaponComponent ? WeaponComponent->GetCurrentWeaponAmmoData(AmmoData) : false;
}

bool USTMPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent =
        STMUtils::GetSTMPlayerComponent<USTMHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

bool USTMPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer(); 
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

void USTMPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTMPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
}

void USTMPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    const auto HealthComponent =
        STMUtils::GetSTMPlayerComponent<USTMHealthComponent>(NewPawn);
    if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
            HealthComponent->OnHealthChanged.AddUObject(this, &USTMPlayerHUDWidget::OnHealthChanged);
    UpdateHealthBar();
}

void USTMPlayerHUDWidget::OnHealthChanged(const float Health, const float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();
        if (!IsAnimationPlaying(DamageAnimation))
            PlayAnimation(DamageAnimation);
    }
    UpdateHealthBar();
}

int32 USTMPlayerHUDWidget::GetKillsNum() const
{
    const auto Controller = GetOwningPlayer();
    if (!Controller) return 0;
    const auto PlayerState = Cast<ASTMPlayerState>(Controller->PlayerState);
    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

void USTMPlayerHUDWidget::UpdateHealthBar() const
{
    if (!HealthProgressBar) return;
    HealthProgressBar->SetFillColorAndOpacity
        (GetHealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
}

FString USTMPlayerHUDWidget::FormatBullets(const int32 BulletsNum) const
{
    constexpr int32 MaxLen = 3;
    constexpr TCHAR PrefixSymbol = '0';
    auto BulletStr = FString::FromInt(BulletsNum);
    const auto SymbolsNumToAdd = MaxLen - BulletStr.Len();
    if (SymbolsNumToAdd > 0)
        BulletStr = FString::ChrN(SymbolsNumToAdd, PrefixSymbol).Append(BulletStr);
    return BulletStr;
}




