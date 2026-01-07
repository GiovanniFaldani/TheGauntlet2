// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "CPP_ActionVolume.generated.h"

// Define types of volume behavior
UENUM(BlueprintType)
enum class EVolumeType : uint8
{
	FallZone   UMETA(DisplayName = "Fall zone"),
	WinZone    UMETA(DisplayName = "Win Zone")
};

UCLASS()
class THEGAUNTLET2_API ACPP_ActionVolume : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ACPP_ActionVolume();

public:
	// Event trigger volume
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UBoxComponent* TriggerBox;

	// Behavior dropdown menu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Volume Settings")
	EVolumeType VolumeType;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
