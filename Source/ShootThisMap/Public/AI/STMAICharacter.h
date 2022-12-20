
#pragma once

#include "CoreMinimal.h"
#include "Player/STMBaseCharacter.h"
#include "STMAICharacter.generated.h"

class UBehaviorTree;
class UWidgetComponent;

UCLASS()
class SHOOTTHISMAP_API ASTMAICharacter : public ASTMBaseCharacter
{
    GENERATED_BODY()
    
public:
    ASTMAICharacter(const FObjectInitializer& ObjInit);
    virtual void Tick(float DeltaTime) override;
    
protected:
    virtual void BeginPlay() override;
    virtual void OnDeath() override;
    virtual void OnHealthChanged(const float Health, const float HealthDelta) const override;

private:
    void UpdateHealthWidgetVisibility() const;
    
public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    TObjectPtr<UBehaviorTree> BehaviorTreeAsset;
    
protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    TObjectPtr<UWidgetComponent> HealthWidgetComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthVisibilityDistance = 1000.0f;
    
protected:
private:
    
	
};
