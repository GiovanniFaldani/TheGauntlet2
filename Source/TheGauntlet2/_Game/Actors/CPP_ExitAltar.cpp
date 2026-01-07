// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Actors/CPP_ExitAltar.h"

// Sets default values
ACPP_ExitAltar::ACPP_ExitAltar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ArtifactSocket = CreateDefaultSubobject<USceneComponent>(TEXT("ArtifactSocket"));
	ArtifactSocket->SetupAttachment(RootComponent);
	ArtifactSocket->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
}

// Called when the game starts or when spawned
void ACPP_ExitAltar::BeginPlay()
{
	Super::BeginPlay();

	// set color
	if (Mesh && Mesh->GetMaterial(0))
	{
		// Init dynamic material based on static material assigned in editor
		DynamicMat = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);

		UpdateColor(FColor::Purple);
	}
	
}

// Called every frame
void ACPP_ExitAltar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_ExitAltar::Interact_Implementation(AActor* Interacter)
{
	// check that Interacter is Player class
}

FTransform ACPP_ExitAltar::GetSocketRelativeTransform()
{
	return ArtifactSocket->GetRelativeTransform();
}

void ACPP_ExitAltar::UpdateColor(FColor NewColor)
{
	if (DynamicMat)
	{
		DynamicMat->SetVectorParameterValue(TEXT("Color"), NewColor);
		Mesh->SetMaterial(0, DynamicMat);
	}
}

