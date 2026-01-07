// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
//#include "CPP_TimerLever.h"
#include "CPP_Turret.generated.h"

UCLASS()
class THEGAUNTLET2_API ACPP_Turret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_Turret();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	TSubclassOf<AActor> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret", meta = (ClampMin = "1"))
	int32 ProjectilePoolSize;

	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	//ACPP_TimerLever* LinkedLever;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret", meta = (ClampMin = "0.01"))
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	USceneComponent* ShotSocket;

	UFUNCTION(BlueprintCallable, Category = "Turret")
	void ToggleTurretState();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	FTimerHandle FireTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	bool bIsActive = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret")
	UMaterialInstanceDynamic* DynamicMat;

	UFUNCTION(BlueprintCallable, Category = "Turret")
	void FireProjectile();

	UFUNCTION(BlueprintCallable, Category = "Turret")
	void UpdateColor(FColor NewColor);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
