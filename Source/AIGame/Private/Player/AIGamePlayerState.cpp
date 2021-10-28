// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AIGamePlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogPlayerState, All, All);

void AAIGamePlayerState::LogInfo()
{
	UE_LOG(LogPlayerState, Display, TEXT("Points: %i"), PointsNum);
}