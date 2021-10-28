// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "AIGameCoreTypes.h"
#include "AIGameGameMode.generated.h"

class AAIController;

UCLASS()
class AIGAME_API AAIGameGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AAIGameGameMode();

	virtual void StartPlay() override;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	void AddPoints(AAIController* VictimController);

	int32 GetRoundSecondsRemaining() const { return RoundCountDown; }


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "2", ClampMax = "10"))
	int32 AIPlayers = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
	int32 RoundTime = 2;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FAIData AIData;

private:

	int32 RoundCountDown = 0;
	FTimerHandle GameRoundTimeHadle;

	void SpawnBots();
	void StartRound();
	void GameTimerUpdate();

	void CreateNamesInfo();

	void LogPlayerInfo();

	void GameOver();
};



