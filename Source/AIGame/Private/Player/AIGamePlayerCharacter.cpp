// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AIGamePlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/AIGameInventoryComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAIGamePlayerCharacter::AAIGamePlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	PrimaryActorTick.bCanEverTick = true;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false; 
}

void AAIGamePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AAIGamePlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//check(InventoryComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &AAIGamePlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AAIGamePlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookRight", this, &AAIGameBaseCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AAIGameBaseCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAction("ChooseCube", IE_Pressed, InventoryComponent, &UAIGameInventoryComponent::ChooseCube);
	PlayerInputComponent->BindAction("ChooseSphere", IE_Pressed, InventoryComponent, &UAIGameInventoryComponent::ChooseSphere);
	PlayerInputComponent->BindAction("Throw", IE_Pressed, InventoryComponent, &UAIGameInventoryComponent::ThrowObject);
	
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);
	
}

void AAIGamePlayerCharacter::MoveForward(float Value)
{
	IsMovingForward = Value > 0.0f;
	AddMovementInput(GetActorForwardVector(), Value);
}

void AAIGamePlayerCharacter::MoveRight(float Value)
{
	AddMovementInput(GetActorRightVector(), Value);
}
