
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STMBaseCharacter.generated.h"

class USTMHealthComponent;
class USTMWeaponComponent;
class USoundCue;

UCLASS()
class SHOOTTHISMAP_API ASTMBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
    ASTMBaseCharacter(const FObjectInitializer& ObjInit);
    virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    virtual bool IsRunning() const;
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;
    
    FORCEINLINE constexpr void SetPlayerColor(const FLinearColor& LinearColor);
    
protected:
	virtual void BeginPlay() override;
    virtual void OnDeath();
    virtual void OnHealthChanged(const float Health, const float HealthDelta) const;

public:
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USTMHealthComponent> HealthComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTMWeaponComponent* WeaponComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    TObjectPtr<UAnimMontage> DeathAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Material")
    FName MaterialColorName = "Paint Color";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
    TObjectPtr<USoundCue> DeathSound;

    bool WantsToRun = false;
    bool IsMovingForward = false;
    
private:
};
