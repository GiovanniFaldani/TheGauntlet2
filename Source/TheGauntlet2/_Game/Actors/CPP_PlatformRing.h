// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_SwitchLever.h"
#include "CPP_PlatformRing.generated.h"

UCLASS()
class THEGAUNTLET2_API ACPP_PlatformRing : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_PlatformRing();

	UFUNCTION(BlueprintCallable, Category = "Platform Ring")
	void ToggleMovement();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Ring")
	ACPP_SwitchLever* LinkedSwitch;

	UPROPERTY(EditAnywhere, Category = "Platform Ring")
	TSubclassOf<AActor> PlatformActor;

	UPROPERTY(EditAnywhere, Category = "Platform Ring", meta = (ClampMin = "1"))
	int NumPlatforms;

	UPROPERTY(EditAnywhere, Category = "Platform Ring")
	float Radius;

	UPROPERTY(EditAnywhere, Category = "Platform Ring")
	float RotationSpeed; // speed in degrees

	UPROPERTY(EditAnywhere, Category = "Platform Ring")
	USceneComponent* PivotRoot;

	UPROPERTY(EditAnywhere, Category = "Platform Ring")
	bool bIsActive;

	UPROPERTY()
	TArray<AActor*> Platforms;

	float CurrentAngle;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
