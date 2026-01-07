// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Interactable.h"
#include "CPP_ExitAltar.generated.h"

UCLASS()
class THEGAUNTLET2_API ACPP_ExitAltar : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_ExitAltar();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Altar")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Altar")
	UMaterialInstanceDynamic* DynamicMat;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Altar")
	USceneComponent* ArtifactSocket;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* Interacter) override;

	UFUNCTION(BlueprintCallable, Category = "Altar")
	FTransform GetSocketRelativeTransform();
};
