// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/AIGameBaseCharacter.h"
#include "AIGamePlayerCharacter.generated.h"

class UCameraComponent;
class UAIGameInventoryComponent;
class USceneComponent;
class USpringArmComponent;
class USphereComponent;

UCLASS()
class AIGAME_API AAIGamePlayerCharacter : public AAIGameBaseCharacter
{
	GENERATED_BODY()
	
public:
	AAIGamePlayerCharacter(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	class UCameraComponent* FollowCamera;

	virtual void BeginPlay() override;

public:
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	bool IsMovingForward = false;

	void MoveForward(float Value);
	void MoveRight(float Value);
	
};
