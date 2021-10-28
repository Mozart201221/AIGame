// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AIGameThrowObject.generated.h"

class UStaticMeshComponent;
class UProjectileMovementComponent;

UCLASS()
class AIGAME_API AAIGameThrowObject : public AActor
{
	GENERATED_BODY()
	
public:	
	AAIGameThrowObject();

public:	
	virtual void Tick(float DeltaTime) override;

	void ActivateProjectile();

	void UpdateVelocity();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* ObjectMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;

	virtual void BeginPlay() override;

};
