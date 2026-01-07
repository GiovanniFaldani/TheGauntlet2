// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Actors/CPP_PlatformRing.h"

// Sets default values
ACPP_PlatformRing::ACPP_PlatformRing()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    // create center pivot
    PivotRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PivotRoot"));
    RootComponent = PivotRoot;

    // defaults
    //LinkedSwitch = nullptr;
    bIsActive = false;
    CurrentAngle = 0.f;
    NumPlatforms = 4;
    Radius = 400.f;
    RotationSpeed = 50.f;
}

// Called when the game starts or when spawned
void ACPP_PlatformRing::BeginPlay()
{
	Super::BeginPlay();

    // check for mesh
    if (!PlatformActor)
    {
        UE_LOG(LogTemp, Error, TEXT("PlatformActor unassigned in %s"), *GetName());
        return;
    }

    // check that there is a switch assigned to this platform ring and add events
    //if (IsValid(LinkedSwitch))
    //{
    //    LinkedSwitch->onSwitchOn.BindUObject(this, &ACPP_PlatformRing::ToggleMovement);
    //    LinkedSwitch->onSwitchOff.BindUObject(this, &ACPP_PlatformRing::ToggleMovement);
    //}

    // create specified number of platforms
    for (int i = 0; i < NumPlatforms; i++)
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;

        ACPP_Platform* NewPlat = Cast<ACPP_Platform>(GetWorld()->SpawnActor<AActor>(PlatformActor, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams));

        if (IsValid(NewPlat))
        {
            float InitialAngle = i * (360.0f / NumPlatforms);
            float RadAngle = FMath::DegreesToRadians(InitialAngle);
            FVector LocalPos = FVector(FMath::Cos(RadAngle) * Radius, FMath::Sin(RadAngle) * Radius, 0.0f);

            NewPlat->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
            NewPlat->SetActorRelativeLocation(LocalPos);
            Platforms.Add(NewPlat);
        }
    }

    // Init color
    UpdateColor(FColor::Blue);
}

// Called every frame
void ACPP_PlatformRing::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (!bIsActive) return;

    CurrentAngle += RotationSpeed * DeltaTime;

    CurrentAngle = FMath::Fmod(CurrentAngle, 360); // clip between 0 and 360 degrees

    for (int i = 0; i < Platforms.Num(); i++)
    {
        if (Platforms[i])
        {
            float InitialAngle = i * (360.0f / NumPlatforms);
            float TotalAngleDeg = CurrentAngle + InitialAngle;
            float TotalAngleRad = FMath::DegreesToRadians(TotalAngleDeg);

            // local coordinates
            FVector NewLocalPos = FVector(
                FMath::Cos(TotalAngleRad) * Radius,
                FMath::Sin(TotalAngleRad) * Radius,
                0.0f
            );

            // Update relative location wrt pivot
            Platforms[i]->SetActorRelativeLocation(NewLocalPos);
        }
    }
}

void ACPP_PlatformRing::ToggleMovement()
{
    bIsActive = !bIsActive;
    if(bIsActive)
    {
        UpdateColor(FColor::Green);
    }
    else
    {
        UpdateColor(FColor::Blue);
	}
}

void ACPP_PlatformRing::UpdateColor(FColor NewColor)
{
    for (int i = 0; i < Platforms.Num(); i++)
    {
        Platforms[i]->UpdateColor(NewColor);
    }
}

