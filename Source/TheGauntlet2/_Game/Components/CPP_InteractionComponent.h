// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Interfaces/Interactable.h"
#include "CPP_InteractionComponent.generated.h"

DECLARE_DELEGATE(OnFindInteractable)
DECLARE_DELEGATE(OnLoseInteractable)

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class THEGAUNTLET2_API UCPP_InteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// delegates for HUD
	OnFindInteractable onFindInteractable;
	OnLoseInteractable onLoseInteractable;

public:
	//** Trace Interaction Distance
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Interaction)
	float DistanceInteraction = 1500.f;

	//** Radius Interaction Distance
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Interaction)
	float RadiusInteraction = 400.f;

	//** Objects types
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Interaction)
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesToInteract;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Interaction)
	bool bDebugInteraction = false;

	UPROPERTY(VisibleAnywhere, Category = Interaction)
	AActor* ClosestActor;

private:
	//** ActorsToIgnore
	UPROPERTY(VisibleAnywhere, Category = Interaction)
	TArray<AActor*> ActorsToIgnore;

	//** ActorsFound
	UPROPERTY(VisibleAnywhere, Category = Interaction)
	TArray<AActor*> ActorsFound;

public:
	// Sets default values for this component's properties
	UCPP_InteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Interaction Trace Objects
	UFUNCTION(BlueprintCallable, Category = Interaction)
	TArray<AActor*> InteractionTraceObjects(const float Distance, const float Radius);

};
