
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STMCoreTypes.h"
#include "STMGameInstance.generated.h"

UCLASS()
class SHOOTTHISMAP_API USTMGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    FORCEINLINE FLevelData GetStartupLevel() const { return StartupLevel; }
    FORCEINLINE FName GetMenuLevelName() const { return MenuLevelName; }
    FORCEINLINE TArray<FLevelData> GetLevelsData() const { return LevelsData; }
    FORCEINLINE constexpr void SetStartupLevel(const FLevelData& Data) { StartupLevel = Data; }


    
protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;

private:
    FLevelData StartupLevel;
};
