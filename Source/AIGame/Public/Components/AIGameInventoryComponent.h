// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "..\..\AIGameCoreTypes.h"
#include "AIGameInventoryComponent.generated.h"

class AAIGameThrowObject;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class AIGAME_API UAIGameInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAIGameInventoryComponent();

public:	

	FOnSwitchObjectSignature OnObjectSwitch;

	virtual void ChooseCube();
	virtual void ChooseSphere();

	void ChooseObject();

	virtual void ThrowObject();

	void SpawnObjects();
	void AttachObjectToSocket(AAIGameThrowObject* Object, USceneComponent* SceneComponent, const FName& SocketName);
	void DetachObjectToSocket(AAIGameThrowObject* Object, USceneComponent* SceneComponent, const FName& SocketName);

private:
	EObject ChooseCurrentObject;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Object")
	FName ThrowEquipSocketName = "ThrowSocket";

	UPROPERTY()
	AAIGameThrowObject* CurrentObject;

	ACharacter* Character() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Object")
	TSubclassOf<AAIGameThrowObject> SphereObject;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Object")
	TSubclassOf<AAIGameThrowObject> CubeObject;

	virtual void BeginPlay() override;

	FRotator GetControlRotation() const;

	void SetObject(EObject Object);

};
