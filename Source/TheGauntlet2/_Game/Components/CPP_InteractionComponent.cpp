// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Components/CPP_InteractionComponent.h"
#include "Kismet/KismetSystemLibrary.h"

// Sets default values for this component's properties
UCPP_InteractionComponent::UCPP_InteractionComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UCPP_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}


// Called every frame
void UCPP_InteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!GetWorld())
	{
		return;
	}

	ActorsFound = InteractionTraceObjects(DistanceInteraction, RadiusInteraction);
	float Distance;
	float InitDistance = 5000;
	ClosestActor = nullptr;

	for (AActor* Actor : ActorsFound)
	{
		Distance = Actor->GetDistanceTo(GetOwner());

		if (Distance < InitDistance)
		{
			InitDistance = Distance;
			ClosestActor = Actor;
		}
	}

	if (bDebugInteraction && IsValid(ClosestActor))
	{
		DrawDebugSphere(
			GetWorld(),
			ClosestActor->GetActorLocation(),
			200.f,
			12,
			FColor::Emerald,
			false,
			-1.f,
			(uint8)0U,
			10.f
		);

	}

	// TODO add interact message for player here if interactable actor (Push to widget stack ingame)
	if (IsValid(ClosestActor) && ClosestActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		//check(GEngine);
		//GEngine->AddOnScreenDebugMessage(0, 0.1, FColor::Yellow, TEXT("Press E to interact!"));
		onFindInteractable.ExecuteIfBound();
	}
	else
	{
		onLoseInteractable.ExecuteIfBound();
	}
}

TArray<AActor*> UCPP_InteractionComponent::InteractionTraceObjects(const float Distance, const float Radius)
{
	FVector EndTrace = GetOwner()->GetActorLocation() + (GetOwner()->GetActorForwardVector() * Distance);


	TArray<FHitResult> Hits;

	TArray<AActor*> ActorsFoundInternal;

	if (!IsValid(GetWorld()))
	{
		return ActorsFound;
	}

	UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(), // Context to pass, we always pass the world context here
		GetOwner()->GetActorLocation(), // Start Trace
		EndTrace, //End Trace
		Radius, // Radius Trace
		ObjectTypesToInteract, //ObjectTypes
		false, // complex trace
		ActorsToIgnore, //
		bDebugInteraction ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		Hits, // Array HitResult to save hit information
		true // Ignore self
	);

	for (FHitResult HitResult : Hits)
	{
		if (IsValid(HitResult.GetActor()))
		{

			ActorsFoundInternal.AddUnique(HitResult.GetActor());
		}
	}

	// UE LOG
	//UE_LOG(LogTemp, Warning, TEXT("CHARACTER: %s"), *CharacterName);


	return ActorsFoundInternal;
}

