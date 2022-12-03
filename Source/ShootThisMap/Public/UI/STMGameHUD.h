
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STMGameHUD.generated.h"

UCLASS()
class SHOOTTHISMAP_API ASTMGameHUD : public AHUD
{
	GENERATED_BODY()

public:
protected:
    virtual void BeginPlay() override;

private:
public:
protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

private:
};
