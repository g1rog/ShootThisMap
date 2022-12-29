
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
	TArray<FLevelData> GetLevelsData() const { return LevelsData; }

    auto GetStartupLevelData() const { return StartupLevelData; }
	auto GetMenuLevelName() const { return MenuLevelName; }
	void SetStartupLevel(const FLevelData& Data) { StartupLevelData = Data; }
    void ToggleVolume() const;


protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;
	
    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundClass* MasterSoundClass;
    
private:
    FLevelData StartupLevelData;
};
