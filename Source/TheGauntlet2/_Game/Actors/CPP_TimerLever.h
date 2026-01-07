// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Turret.h"
#include "../Interfaces/Interactable.h"
#include "Materials/MaterialInstanceDynamic.h"
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

	// editonly turret pointer
	UPROPERTY(EditInstanceOnly, Category = "Timer Lever")
	ACPP_Turret* LinkedTurret;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Timer Lever")
	void ActivateLever();

	UFUNCTION(BlueprintCallable, Category = "Timer Lever")
	void DeactivateLever();

	UFUNCTION(BlueprintCallable, Category = "Timer Lever")
	void Interact_Implementation(AActor* Interacter);
};
