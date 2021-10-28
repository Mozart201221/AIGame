// Copyright Epic Games, Inc. All Rights Reserved.

#include "AIGameGameMode.h"
#include "Player/AIGameBaseCharacter.h"
#include "Player/AIGamePlayerController.h"
//#include "UI/AIGameGameHUD.h"
#include "AI/AIGameAIController.h"
#include "Player/AIGamePlayerState.h"
#include "EngineUtils.h"
#include "UObject/ConstructorHelpers.h"

DEFINE_LOG_CATEGORY_STATIC(LogAIGameMode, All, All);

AAIGameGameMode::AAIGameGameMode()
{
	DefaultPawnClass = AAIGameBaseCharacter::StaticClass();
	PlayerControllerClass = AAIGamePlayerController::StaticClass();
	//HUDClass = AAIGameGameHUD::StaticClass();
	PlayerStateClass = AAIGamePlayerState::StaticClass();

	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/Player/BP_AIGamePlayerCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AAIGameGameMode::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	StartRound();
}

UClass* AAIGameGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if (InController && InController->IsA<AAIController>())
	{
		return AIPawnClass;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AAIGameGameMode::AddPoints(AAIController* VictimController)
{
	const auto VictimPlayerState = VictimController ? Cast<AAIGamePlayerState>(VictimController->PlayerState) : NULL;
	VictimPlayerState->AddPoint();

}

void AAIGameGameMode::SpawnBots()
{
	if (!GetWorld()) return;

	for (int32 i = 0; i < AIPlayers; ++i)
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto AIController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
		RestartPlayer(AIController);
	}

}

void AAIGameGameMode::StartRound()
{
	GetWorldTimerManager().SetTimer(GameRoundTimeHadle, this, &AAIGameGameMode::GameTimerUpdate, 1.0f, true);
}

void AAIGameGameMode::GameTimerUpdate()
{
	UE_LOG(LogAIGameMode, Display, TEXT("Time: %i"), RoundTime);
	const auto TimerRate = GetWorldTimerManager().GetTimerRate(GameRoundTimeHadle);

	if (--RoundTime == 0)
	{
		GetWorldTimerManager().ClearTimer(GameRoundTimeHadle);
		GameOver();
	}
}

void AAIGameGameMode::CreateNamesInfo()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AAIGamePlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		// Забираем имена из массива

		const auto Names = AIData.Name;
		PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
		
	}
}

void AAIGameGameMode::LogPlayerInfo()
{
	if (!GetWorld()) return;

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto PlayerState = Cast<AAIGamePlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->LogInfo();
	}
}

void AAIGameGameMode::GameOver()
{
	UE_LOG(LogAIGameMode, Display, TEXT("============= GAME OVER ==========="));
	LogPlayerInfo();

	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(NULL);
		}
	}
}

