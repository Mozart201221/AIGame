// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/AIGameInventoryComponent.h"
#include "ThrowObject/AIGameThrowObject.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/Character.h"


DEFINE_LOG_CATEGORY_STATIC(LogObjectComponent, All, All)

UAIGameInventoryComponent::UAIGameInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UAIGameInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UAIGameInventoryComponent::ChooseCube()
{
	SetObject(EObject::CubeObject);
	ChooseObject();
}

void UAIGameInventoryComponent::ChooseSphere()
{
	SetObject(EObject::SphereObject);
	ChooseObject();
}

void UAIGameInventoryComponent::ChooseObject()
{
	SpawnObjects();
}

void UAIGameInventoryComponent::ThrowObject()
{
	const FRotator SpawnRotation = GetControlRotation();
	const FVector SpawnLocation = (Character()->GetMesh()->GetSocketLocation(ThrowEquipSocketName));


	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

	if (!CurrentObject) return;
	

	const FVector UpdateVelocity = Character()->GetVelocity();
	CurrentObject->GetVelocity() + UpdateVelocity;
	CurrentObject->ActivateProjectile();
	CurrentObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

}

void UAIGameInventoryComponent::SpawnObjects()
{
	if (CurrentObject)
	{
		CurrentObject->Destroy();
	}

	if (EObject::SphereObject == ChooseCurrentObject)
	{
		CurrentObject = GetWorld()->SpawnActor<AAIGameThrowObject>(SphereObject);
	}
	else if(EObject::CubeObject == ChooseCurrentObject)
	{
		CurrentObject = GetWorld()->SpawnActor<AAIGameThrowObject>(CubeObject);
	}

	AttachObjectToSocket(CurrentObject, Character()->GetMesh(), ThrowEquipSocketName);
	
}



void UAIGameInventoryComponent::AttachObjectToSocket(AAIGameThrowObject* Object, USceneComponent* SceneComponent, const FName& SocketName)
{
	if (!Object || !SceneComponent) return;
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Object->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UAIGameInventoryComponent::DetachObjectToSocket(AAIGameThrowObject* Object, USceneComponent* SceneComponent, const FName& SocketName)
{
	CurrentObject->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	
}

FRotator UAIGameInventoryComponent::GetControlRotation() const
{
	const auto Controller = Character()->GetController<APlayerController>();
	return Controller ? Controller->GetControlRotation() : FRotator::ZeroRotator;
}

ACharacter* UAIGameInventoryComponent::Character() const
{
	const auto AIGamePlayerCharacter = Cast<ACharacter>(GetOwner());
	return AIGamePlayerCharacter;
}

void UAIGameInventoryComponent::SetObject(EObject Object)
{
	if (ChooseCurrentObject == Object) return;

	ChooseCurrentObject = Object;
	OnObjectSwitch.Broadcast(ChooseCurrentObject);
}
