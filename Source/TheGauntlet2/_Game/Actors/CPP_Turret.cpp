// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Actors/CPP_Turret.h"
#include "../Subsystems/CPP_ObjectPoolSubsystem.h"

// Sets default values
ACPP_Turret::ACPP_Turret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	RootComponent = Mesh;

	ShotSocket = CreateDefaultSubobject<USceneComponent>(TEXT("ShotSocket"));
	ShotSocket->SetupAttachment(Mesh);
	ShotSocket->SetRelativeLocation(FVector(50.f, 0.f, 100.f));
}

void ACPP_Turret::ToggleTurretState()
{
	if (bIsActive)
	{
		bIsActive = false;
		GetWorldTimerManager().PauseTimer(FireTimerHandle);
		UpdateColor(FColor::Blue);
	}
	else
	{
		bIsActive = true;
		GetWorldTimerManager().UnPauseTimer(FireTimerHandle);
		UpdateColor(FColor::Orange);
	}

}

// Called when the game starts or when spawned
void ACPP_Turret::BeginPlay()
{
	Super::BeginPlay();
	
	// initialize projectile pool
	if (ProjectileClass)
	{
		if (UCPP_ObjectPoolSubsystem* Subsystem = GetWorld()->GetSubsystem<UCPP_ObjectPoolSubsystem>())
		{
			Subsystem->AddPool(ProjectileClass, ProjectilePoolSize);
		}
	}

	// set color
	if (Mesh && Mesh->GetMaterial(0))
	{
		// Init dynamic material based on static material assigned in editor
		DynamicMat = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);

		UpdateColor(FColor::Orange);
	}

	// add delegates to linked lever
	/*if (IsValid(LinkedLever))
	{
		LinkedLever->onLeverPull.BindUObject(this, &ACPP_Turret::ToggleTurretState);
		LinkedLever->onLeverUndo.BindUObject(this, &ACPP_Turret::ToggleTurretState);
	}*/

	// start timer
	GetWorld()->GetTimerManager().SetTimer(
		FireTimerHandle,
		this,
		&ACPP_Turret::FireProjectile,
		1.f / FireRate,
		true
	);
}

// Called every frame
void ACPP_Turret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// debug info
	if (ProjectileClass)
	{
		if (UCPP_ObjectPoolSubsystem* Subsystem = GetWorld()->GetSubsystem<UCPP_ObjectPoolSubsystem>())
		{
			int32 Total = 0;
			int32 Active = 0;
			Subsystem->GetPoolStats(ProjectileClass, Total, Active);

			FString DebugMsg = FString::Printf(TEXT("Pool Size: %d | Active: %d"), Total, Active);
			check(GEngine);
			GEngine->AddOnScreenDebugMessage(10, 0.0f, FColor::Cyan, DebugMsg);
		}
	}
}

void ACPP_Turret::FireProjectile()
{
	if (!bIsActive || !IsValid(ProjectileClass)) return;

	UCPP_ObjectPoolSubsystem* Subsystem = GetWorld()->GetSubsystem<UCPP_ObjectPoolSubsystem>();
	if (!Subsystem) return;

	// get object from pool
	TScriptInterface<IObjectPoolInterface> PooledObj = Subsystem->GetObjectFromPool(ProjectileClass);

	if (AActor* Projectile = Cast<AActor>(PooledObj.GetObject()))
	{
		Projectile->SetActorLocation(ShotSocket->GetComponentLocation());
		Projectile->SetActorRotation(GetActorRotation());
		FObjectPoolActivationData ActivationData;
		IObjectPoolInterface::Execute_Activate(Projectile, ActivationData);
	}

	// clean and restart timer
	GetWorld()->GetTimerManager().ClearTimer(FireTimerHandle);
	GetWorld()->GetTimerManager().SetTimer(
		FireTimerHandle,
		this,
		&ACPP_Turret::FireProjectile,
		1.f / FireRate,
		true
	);
}

void ACPP_Turret::UpdateColor(FColor NewColor)
{
	if (DynamicMat)
	{
		DynamicMat->SetVectorParameterValue(TEXT("Color"), NewColor);
		Mesh->SetMaterial(0, DynamicMat);
	}
}

