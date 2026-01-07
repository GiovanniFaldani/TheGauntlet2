// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Actors/CPP_TimerLever.h"

// Sets default values
ACPP_TimerLever::ACPP_TimerLever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Add switch mesh
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
}

// Called when the game starts or when spawned
void ACPP_TimerLever::BeginPlay()
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

	bIsActive = false;
}

// Called every frame
void ACPP_TimerLever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_TimerLever::ActivateLever()
{
	check(GEngine);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Lever Activated"));

	//onLeverPull.ExecuteIfBound();
	bIsActive = true;

	DynamicMaterialInstance->SetVectorParameterValue(FName("Color"), FLinearColor::Green);

	// update turret
	if(IsValid(LinkedTurret)) LinkedTurret->ToggleTurretState();

	// Start timer
	GetWorld()->GetTimerManager().SetTimer(
		LeverTimerHandle,
		this,
		&ACPP_TimerLever::DeactivateLever,
		LeverTimer,
		false
	);
}

void ACPP_TimerLever::DeactivateLever()
{
	check(GEngine);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, TEXT("Lever Deactivated"));

	//onLeverUndo.ExecuteIfBound();
	bIsActive = false;

	DynamicMaterialInstance->SetVectorParameterValue(FName("Color"), FLinearColor::Red);

	// update turret
	if (IsValid(LinkedTurret)) LinkedTurret->ToggleTurretState();

	GetWorld()->GetTimerManager().ClearTimer(LeverTimerHandle);
}

void ACPP_TimerLever::Interact_Implementation(AActor* Interacter)
{
	if(!bIsActive) ActivateLever();
}

