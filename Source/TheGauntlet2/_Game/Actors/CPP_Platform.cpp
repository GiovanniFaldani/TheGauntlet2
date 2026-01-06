// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Actors/CPP_Platform.h"

// Sets default values
ACPP_Platform::ACPP_Platform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ACPP_Platform::BeginPlay()
{
	Super::BeginPlay();
	
	if (Mesh && Mesh->GetMaterial(0))
	{
		// Init dynamic material based on static material assigned in editor
		DynamicMat = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);

		if (DynamicMat)
		{
			Mesh->SetMaterial(0, DynamicMat);
		}
	}
}

// Called every frame
void ACPP_Platform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Platform::UpdateColor(FColor NewColor)
{
	if (DynamicMat)
	{
		DynamicMat->SetVectorParameterValue(FName("Color"), NewColor);
	}
}

