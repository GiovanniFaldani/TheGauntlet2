// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Door.generated.h"

UCLASS()
class THEGAUNTLET2_API ACPP_Door : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Door();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Door")
	UStaticMeshComponent* Mesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Door")
	bool bIsOpen;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleDoor();
};
