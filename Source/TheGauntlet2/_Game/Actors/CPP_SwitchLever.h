// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CPP_Door.h"
#include "CPP_PlatformRing.h"
#include "../Interfaces/Interactable.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "CPP_SwitchLever.generated.h"

//DECLARE_DELEGATE(OnSwitchOn)
//DECLARE_DELEGATE(OnSwitchOff)

UCLASS()
class THEGAUNTLET2_API ACPP_SwitchLever : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACPP_SwitchLever();

	// delegates
	//OnSwitchOn onSwitchOn;
	//OnSwitchOff onSwitchOff;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Switch Lever")
	bool bIsOn;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Switch Lever")
	UMaterialInstanceDynamic* DynamicMaterialInstance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Switch Lever")
	UStaticMeshComponent* Mesh;

	// editonly actor pointers
	UPROPERTY(EditInstanceOnly, Category = "Switch Lever")
	ACPP_Door* LinkedDoor;

	UPROPERTY(EditInstanceOnly, Category = "Switch Lever")
	ACPP_PlatformRing* LinkedPlatforms;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Switch Lever")
	void ActivateSwitch();

	UFUNCTION(BlueprintCallable, Category = "Switch Lever")
	void DeactivateSwitch();

	UFUNCTION(BlueprintCallable, Category = "Switch Lever")
	virtual void Interact(AActor* Interacter) override;

};
