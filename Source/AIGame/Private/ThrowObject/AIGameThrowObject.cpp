// Fill out your copyright notice in the Description page of Project Settings.


#include "ThrowObject/AIGameThrowObject.h"
#include "Components/AIGameInventoryComponent.h"
#include "GameFramework/Character.h"
#include "Player/AIGamePlayerCharacter.h"
#include "GameFramework/Controller.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

AAIGameThrowObject::AAIGameThrowObject()
{
	PrimaryActorTick.bCanEverTick = true;

	ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>("ObjectMesh");
	SetRootComponent(ObjectMesh);

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = ObjectMesh;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Deactivate();

}

void AAIGameThrowObject::ActivateProjectile()
{
	ProjectileMovement->Activate();
	//UpdateVelocity();
	//ProjectileMovement->Velocity + Character->GetVelocity();
}

void AAIGameThrowObject::BeginPlay()
{
	Super::BeginPlay();

	check(ObjectMesh);
	
}

void AAIGameThrowObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
