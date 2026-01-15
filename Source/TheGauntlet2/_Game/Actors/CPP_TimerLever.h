// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Turret.h"
#include "CPP_Door.h"
#include "CPP_PlatformRing.h"
#include "../Interfaces/Interactable.h"
#include "../CPP_PlayerController.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Kismet/GameplayStatics.h"

#include "CPP_TimerLever.generated.h"

//DECLARE_DELEGATE(OnLeverPull)
//DECLARE_DELEGATE(OnLeverUndo)

UCLASS()
class THEGAUNTLET2_API ACPP_TimerLever : public AActor, public IInteractable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACPP_TimerLever();

	// delegates
	//OnLeverPull onLeverPull;
	//OnLeverUndo onLeverUndo;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Timer Lever")
	bool bIsActive;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Timer Lever")
	float LeverTimer;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Timer Lever")
	FTimerHandle LeverTimerHandle;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Timer Lever")
	UMaterialInstanceDynamic* DynamicMaterialInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Timer Lever")
	UStaticMeshComponent* Mesh;

	// editonly actor pointers
	UPROPERTY(EditInstanceOnly, Category = "Timer Lever")
	ACPP_Turret* LinkedTurret;

	UPROPERTY(EditInstanceOnly, Category = "Timer Lever")
	ACPP_Door* LinkedDoor;

	UPROPERTY(EditInstanceOnly, Category = "Timer Lever")
	ACPP_PlatformRing* LinkedPlatforms;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Timer Lever")
	void ActivateLever();

	UFUNCTION(BlueprintCallable, Category = "Timer Lever")
	void DeactivateLever();

	UFUNCTION(BlueprintCallable, Category = "Timer Lever")
	virtual void Interact(AActor* Interacter) override;
};
