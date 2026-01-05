// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Actors/CPP_Turret.h"

// Sets default values
ACPP_Turret::ACPP_Turret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACPP_Turret::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACPP_Turret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

