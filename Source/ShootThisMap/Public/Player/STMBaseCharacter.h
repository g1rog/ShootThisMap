
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STMBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USTMHealthComponent;
class UTextRenderComponent;
class USTMWeaponComponent;

UCLASS()
class SHOOTTHISMAP_API ASTMBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
    ASTMBaseCharacter(const FObjectInitializer& ObjInit);
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsRunning() const;
    
    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

    virtual void Tick(float DeltaTime) override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
protected:
	virtual void BeginPlay() override;
    virtual void OnDeath();

private:
    FORCEINLINE void MoveForward(const float Amount);
    FORCEINLINE void MoveRight(const float Amount);
    FORCEINLINE void OnStartRunning();
    FORCEINLINE void OnStopRunning();

    void OnHealthChanged(const float Health, const float HealthDelta) const;
    
public:
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UCameraComponent> CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USpringArmComponent> SpringArmComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USTMHealthComponent> HealthComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UTextRenderComponent> HealthTextComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USTMWeaponComponent* WeaponComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animations")
    TObjectPtr<UAnimMontage> DeathAnimMontage;

private:
    bool WantsToRun = false;
    bool IsMovingForward = false;
    
};
