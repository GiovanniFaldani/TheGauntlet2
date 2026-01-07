// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Actors/CPP_SwitchLever.h"

// Sets default values
ACPP_SwitchLever::ACPP_SwitchLever()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add switch mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ACPP_SwitchLever::BeginPlay()
{
	Super::BeginPlay();

	if (Mesh && Mesh->GetMaterial(0))
	{
		// Init dynamic material based on static material assigned in editor
		DynamicMaterialInstance = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);

		if (DynamicMaterialInstance)
		{
			Mesh->SetMaterial(0, DynamicMaterialInstance);
			DynamicMaterialInstance->SetVectorParameterValue(FName("Color"), FLinearColor::Red);
		}
	}

	bIsOn = false;
}

// Called every frame
void ACPP_SwitchLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_SwitchLever::ActivateSwitch()
{
	check(GEngine);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Switch Activated"));

	//onSwitchOn.ExecuteIfBound();
	bIsOn = true;

	if (IsValid(LinkedDoor)) LinkedDoor->ToggleDoor();
	if (IsValid(LinkedPlatforms)) LinkedPlatforms->ToggleMovement();

	DynamicMaterialInstance->SetVectorParameterValue(FName("Color"), FLinearColor::Green);
}

void ACPP_SwitchLever::DeactivateSwitch()
{
	check(GEngine);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Switch Deactivated"));

	//onSwitchOff.ExecuteIfBound();
	bIsOn = false;

	if (IsValid(LinkedDoor)) LinkedDoor->ToggleDoor();
	if (IsValid(LinkedPlatforms)) LinkedPlatforms->ToggleMovement();

	DynamicMaterialInstance->SetVectorParameterValue(FName("Color"), FLinearColor::Red);
}

void ACPP_SwitchLever::Interact_Implementation(AActor* Interacter)
{
	if (bIsOn)
	{
		DeactivateSwitch();
	}
	else
	{
		ActivateSwitch();
	}
}

