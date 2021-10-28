// Copyright Epic Games, Inc. All Rights Reserved.

#include "Player/AIGameBaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Components/AIGameCharacterMovementComponent.h"
#include "Components/AIGameInventoryComponent.h"
#include "GameFramework/Controller.h"


AAIGameBaseCharacter::AAIGameBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<UAIGameCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;
	InventoryComponent = CreateDefaultSubobject<UAIGameInventoryComponent>("InventoryComponent");
}

void AAIGameBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GetCharacterMovement());
}