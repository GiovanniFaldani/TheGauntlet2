// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Actors/CPP_Artifact.h"

// Sets default values
ACPP_Artifact::ACPP_Artifact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Artifact::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Artifact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

