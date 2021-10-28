#pragma once
#include "AIGameCoreTypes.generated.h"

// Object

UENUM(BlueprintType)
enum class EObject : uint8
{
	Nothing = 0,
	SphereObject,
	CubeObject
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnSwitchObjectSignature, EObject);

USTRUCT(BlueprintType)
struct FAIData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AISettings")
	TArray<FString> Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AISettings", meta = (ClampMin = "0"))
	int32 MaxWalkSpeed = 600;

};