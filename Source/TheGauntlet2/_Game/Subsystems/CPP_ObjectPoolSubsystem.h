// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "../Interfaces/ObjectPoolInterface.h"
#include "CPP_ObjectPoolSubsystem.generated.h"

/**
 *
 */

USTRUCT(BlueprintType)
struct FObjectPool
{
	GENERATED_BODY()

	// Array with the pointers of the USABLE objects IN this pool
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Object Pool Struct")
	TArray<TScriptInterface<IObjectPoolInterface>> UsablePoolingObjects;

	// Array with the pointers of the ACTIVE IN SCENE objects FROM this pool
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Object Pool Struct")
	TArray<TScriptInterface<IObjectPoolInterface>> ActivePoolingObjects;

};

UCLASS()
class THEGAUNTLET2_API UCPP_ObjectPoolSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()

public:
	// Map with the Objects we want to pool
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Object Pool SubSystem")
	TMap<TSubclassOf<AActor>, FObjectPool> ObjectPoolMap;

	// Add a pool of objects
	UFUNCTION(BlueprintCallable, Category = "Object Pool SubSystem")
	void AddPool(TSubclassOf<AActor> ClassPool, int32 InitialSize = 50);

	UFUNCTION(BlueprintCallable, Category = "Object Pool SubSystem")
	TScriptInterface<IObjectPoolInterface> GetObjectFromPool(TSubclassOf<AActor> ClassPool);

	UFUNCTION(BlueprintCallable, Category = "Object Pool SubSystem")
	void ReturnObjectToPool(TSubclassOf<AActor> ClassPool, TScriptInterface<IObjectPoolInterface> ActorToReturn);

	UFUNCTION(BlueprintCallable, Category = "Pooling")
	void GetPoolStats(TSubclassOf<AActor> PoolClass, int32& OutTotal, int32& OutActive);
};
