
#pragma once

#include "CoreMinimal.h"
#include "Player/STMBaseCharacter.h"
#include "STMPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class SHOOTTHISMAP_API ASTMPlayerCharacter : public ASTMBaseCharacter
{
    GENERATED_BODY()
    
public:
    ASTMPlayerCharacter(const FObjectInitializer& ObjInit);
    virtual bool IsRunning() const override;
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    
protected:
    virtual void BeginPlay() override;
    virtual void OnDeath() override;
    
private:
    UFUNCTION()
    void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

    UFUNCTION()
    void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
    
	void MoveForward(const float Amount);
	void MoveRight(const float Amount);
	void OnStartRunning();
	void OnStopRunning();
    void CheckCameraOverlap() const;
    
    
public:
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USpringArmComponent> SpringArmComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UCameraComponent> CameraComponent;
    
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<USphereComponent> CameraCollisionComponent;
};
