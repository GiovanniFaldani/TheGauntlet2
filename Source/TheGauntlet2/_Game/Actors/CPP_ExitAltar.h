// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "../Interfaces/Interactable.h"
#include "../CPP_Character.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "../Subsystems/CPP_QuestSubsystem.h"
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Altar")
	USceneComponent* ArtifactSocket;

	// quest ID must be present in data table
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Altar")
	FName QuestID = "Quest1";

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Interact_Implementation(AActor* Interacter) override;

	UFUNCTION(BlueprintCallable, Category = "Altar")
	USceneComponent* GetArtifactSocket();

	UFUNCTION(BlueprintCallable, Category = "Altar")
	void OnVictoryAssetsLoaded(UNiagaraSystem* VFX, USoundBase* SFX);

	void UpdateColor(FColor NewColor);
};
