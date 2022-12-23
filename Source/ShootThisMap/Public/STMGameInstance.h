
#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STMCoreTypes.h"
#include "STMGameInstance.generated.h"

class USoundClass;

UCLASS()
class SHOOTTHISMAP_API USTMGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:
    FORCEINLINE FLevelData GetStartupLevel() const { return StartupLevel; }
    FORCEINLINE FName GetMenuLevelName() const { return MenuLevelName; }
    FORCEINLINE TArray<FLevelData> GetLevelsData() const { return LevelsData; }
    FORCEINLINE constexpr void SetStartupLevel(const FLevelData& Data) { StartupLevel = Data; }
    FORCEINLINE void ToggleVolume() const;

protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundClass* MasterSoundClass;
    
private:
    FLevelData StartupLevel;
};
