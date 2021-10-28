// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIGameAICharacter.generated.h"

class UWidgetComponent;

UCLASS()
class AIGAME_API AAIGameAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAIGameAICharacter();

protected:

	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
