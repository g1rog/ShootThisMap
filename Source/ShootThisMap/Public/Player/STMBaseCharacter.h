
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "STMBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

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

private:
    void MoveForward(const float Amount);
    void MoveRight(const float Amount);
    void OnStartRunning();
    void OnStopRunning();
    
public:
    /**/
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UCameraComponent> CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USpringArmComponent> SpringArmComponent;
    
private:
    bool WantsToRun = false;
    bool IsMovingForward = false;
	

};
