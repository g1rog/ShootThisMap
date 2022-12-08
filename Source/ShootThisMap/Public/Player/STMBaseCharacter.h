
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STMBaseCharacter.generated.h"

class USTMHealthComponent;
class USTMWeaponComponent;

UCLASS()
class SHOOTTHISMAP_API ASTMBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
    ASTMBaseCharacter(const FObjectInitializer& ObjInit);
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    virtual bool IsRunning() const;
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;
    
    virtual void Tick(float DeltaTime) override;
    FORCEINLINE constexpr void SetPlayerColor(const FLinearColor& LinearColor);
    
protected:
	virtual void BeginPlay() override;
    virtual void OnDeath();

private:
    
    void OnHealthChanged(const float Health, const float HealthDelta) const;
    
public:
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USTMHealthComponent> HealthComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTMWeaponComponent* WeaponComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    TObjectPtr<UAnimMontage> DeathAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Material")
    FName MaterialColorName = "Paint Color" ;

    bool WantsToRun = false;
    bool IsMovingForward = false;
private:
    
};
