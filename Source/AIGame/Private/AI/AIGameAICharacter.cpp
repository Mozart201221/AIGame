// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/AIGameAICharacter.h"

#include "AI/AIGameAIController.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AAIGameAICharacter::AAIGameAICharacter()
{

	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = AAIGameAIController::StaticClass();

	PrimaryActorTick.bCanEverTick = false;

	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void AAIGameAICharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAIGameAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


