
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
    FLevelData GetStartupLevel() const { return StartupLevel; }
    FName GetMenuLevelName() const { return MenuLevelName; }
    TArray<FLevelData> GetLevelsData() const { return LevelsData; }
    void SetStartupLevel(const FLevelData& Data) { StartupLevel = Data; }
    void ToggleVolume() const;

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
