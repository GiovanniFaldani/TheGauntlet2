// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Actors/CPP_Artifact.h"
#include "../CPP_Character.h"

// Sets default values
ACPP_Artifact::ACPP_Artifact()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ACPP_Artifact::BeginPlay()
{
	Super::BeginPlay();
	
    // set color
    if (Mesh && Mesh->GetMaterial(0))
    {
        // Init dynamic material based on static material assigned in editor
        DynamicMat = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);

        UpdateColor(FColor::Yellow);
    }
}

// Called every frame
void ACPP_Artifact::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_Artifact::Interact(AActor* Interacter)
{
    ACPP_Character* Player = Cast<ACPP_Character>(Interacter);
    if (!Player) return;

    Mesh->SetSimulatePhysics(false);
    Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	UpdateColor(FColor::Green);

    this->AttachToComponent(Player->GetArtifactSocket(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    Player->SetArtifactCollected(true, this);

}

void ACPP_Artifact::UpdateColor(FColor NewColor)
{
    if (DynamicMat)
    {
        DynamicMat->SetVectorParameterValue(TEXT("Color"), NewColor);
        Mesh->SetMaterial(0, DynamicMat);
    }
}

