// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_ObjectPoolSubsystem.h"
#include "Engine/World.h"

void UCPP_ObjectPoolSubsystem::AddPool(TSubclassOf<AActor> ClassPool, int32 InitialSize)
{
	if (!GetWorld())
	{

		UCPP_ObjectPoolSubsystem* MySubsystem = GetWorld()->GetSubsystem<UCPP_ObjectPoolSubsystem>();
		if (MySubsystem)
		{
			//MySubsystem->AddPool();
		}
		return;
	}

	if (!ClassPool->ImplementsInterface(UObjectPoolInterface::StaticClass()))
	{
		return;
	}

	FObjectPool ObjectPoolToCreate;

	// Se vogliamo aggiungere piu' parametri per lo spawn
	FActorSpawnParameters SpawnParameters;

	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	// Spawn initial actors to use
	for (int i = 0; i < InitialSize; i++)
	{
		// Spawn objects to add in the pool
		AActor* ActorRef = GetWorld()->SpawnActor<AActor>(ClassPool, SpawnParameters);

		// Add the spawned actor to the pool
		ObjectPoolToCreate.UsablePoolingObjects.AddUnique(ActorRef);
	}

	ObjectPoolMap.Add(ClassPool, ObjectPoolToCreate);
}

TScriptInterface<IObjectPoolInterface> UCPP_ObjectPoolSubsystem::GetObjectFromPool(TSubclassOf<AActor> ClassPool)
{
	if (!GetWorld())
	{
		return nullptr;
	}

	if (!ObjectPoolMap.Contains(ClassPool))
	{
		return nullptr;
	}

	if (!ClassPool->ImplementsInterface(UObjectPoolInterface::StaticClass()))
	{
		return nullptr;
	}

	FObjectPool* PoolObject = ObjectPoolMap.Find(ClassPool);

	//ObjectPoolMap.FindOrAdd()

	TScriptInterface<IObjectPoolInterface> ActorToReturn;

	// We control that the pool is not empty
	if (PoolObject->UsablePoolingObjects.IsEmpty())
	{
		// Spawn new object to use, he will auto go back to the pooling system
		FActorSpawnParameters SpawnParameters;

		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		ActorToReturn = GetWorld()->SpawnActor<AActor>(ClassPool, SpawnParameters);

		PoolObject->ActivePoolingObjects.AddUnique(ActorToReturn);
	}
	else
	{
		// Pick the first usable object
		ActorToReturn = PoolObject->UsablePoolingObjects[0];
		// Remove from usable objects
		PoolObject->UsablePoolingObjects.Remove(ActorToReturn);
		// Register it to the current active objects
		PoolObject->ActivePoolingObjects.AddUnique(ActorToReturn);
	}

	return ActorToReturn;
}

void UCPP_ObjectPoolSubsystem::ReturnObjectToPool(TSubclassOf<AActor> ClassPool, TScriptInterface<IObjectPoolInterface> ActorToReturn)
{
	if (!GetWorld())
	{
		return;
	}

	if (!ObjectPoolMap.Contains(ClassPool))
	{
		return;
	}

	if (!ActorToReturn.GetObject()->GetClass()->ImplementsInterface(UObjectPoolInterface::StaticClass()))
	{
		return;
	}

	// Deactivate object pool
	if (ActorToReturn.GetInterface())
	{
		ActorToReturn.GetInterface()->Deactivate();
	}
	else
	{
		IObjectPoolInterface::Execute_Deactivate(ActorToReturn.GetObject());
	}

	// We get the object pool with our pool objects
	FObjectPool* PoolObject = ObjectPoolMap.Find(ClassPool);

	if (!PoolObject->ActivePoolingObjects.Contains(ActorToReturn))
	{
		UE_LOG(LogTemp, Warning, TEXT("Trying to add to the pool an object that wasn't registered before"));
	}

	// unregister from active objects
	PoolObject->ActivePoolingObjects.Remove(ActorToReturn);

	// return back to being use in the pool of usable objects
	PoolObject->UsablePoolingObjects.AddUnique(ActorToReturn);
}

void UCPP_ObjectPoolSubsystem::GetPoolStats(TSubclassOf<AActor> PoolClass, int32& OutTotal, int32& OutActive)
{
	// Identify pool by object class
	if (ObjectPoolMap.Contains(PoolClass))
	{
		FObjectPool& Pool = ObjectPoolMap[PoolClass];
		OutActive = Pool.ActivePoolingObjects.Num();
		int32 Usable = Pool.UsablePoolingObjects.Num();
		OutTotal = OutActive + Usable;
	}
	else
	{
		OutTotal = 0;
		OutActive = 0;
	}
}
