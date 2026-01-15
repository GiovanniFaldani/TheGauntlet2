// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Interactable.h"
#include "../CPP_PlayerController.h"
#include "Kismet/GameplayStatics.h"


#include "CPP_Artifact.generated.h"

UCLASS()
class THEGAUNTLET2_API ACPP_Artifact : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Artifact();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artifact")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Artifact")
	UMaterialInstanceDynamic* DynamicMat;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* Interacter) override;

	void UpdateColor(FColor NewColor);
};
