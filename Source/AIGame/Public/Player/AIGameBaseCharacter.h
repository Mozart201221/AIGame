// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIGameBaseCharacter.generated.h"

class UAIGameInventoryComponent;

UCLASS()
class AIGAME_API AAIGameBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AAIGameBaseCharacter(const FObjectInitializer& ObjInit);


protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAIGameInventoryComponent* InventoryComponent;

	virtual void BeginPlay() override;

public:

};

