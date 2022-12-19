
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STMMenuHUD.generated.h"

UCLASS()
class SHOOTTHISMAP_API ASTMMenuHUD : public AHUD
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;
};
