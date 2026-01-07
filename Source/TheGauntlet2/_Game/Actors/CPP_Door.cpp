// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Actors/CPP_Door.h"

// Sets default values
ACPP_Door::ACPP_Door()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ACPP_Door::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Door::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Door::ToggleDoor()
{
	if(bIsOpen)
	{
		bIsOpen = false;

		// set actor active again
		SetActorHiddenInGame(false);
		SetActorEnableCollision(true);
	}
	else
	{
		bIsOpen = true;
		
		// deactivate actor
		SetActorHiddenInGame(true);
		SetActorEnableCollision(false);
	}
}

