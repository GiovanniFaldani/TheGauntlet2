// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ObjectPoolInterface.generated.h"

USTRUCT(BlueprintType)
struct FObjectPoolActivationData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Object Pool Data")
	FTransform ObjectPoolTransform;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Object Pool Data")
	FName ObjectPoolName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Object Pool Data")
	FString ObjectPoolID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Object Pool Data")
	FText ObjectPoolText;
};

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UObjectPoolInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THEGAUNTLET2_API IObjectPoolInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ObjectPool")
	void Activate(FObjectPoolActivationData ObjectPoolData);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "ObjectPool")
	void Deactivate();

};
