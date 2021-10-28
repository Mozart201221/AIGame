// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "..\..\AIGameCoreTypes.h"
#include "GameFramework/PlayerState.h"
#include "AIGamePlayerState.generated.h"

UCLASS()
class AIGAME_API AAIGamePlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	
	void AddPoint() { ++PointsNum; }
	int32 GetPointsNum() const { return PointsNum; }


	void LogInfo();

private:
	int32 PointsNum = 0;

protected:
/*
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TArray<FPlayerData> PlayerData;
	*/
};
