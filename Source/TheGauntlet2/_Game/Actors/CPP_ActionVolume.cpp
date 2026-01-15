// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Actors/CPP_ActionVolume.h"
#include "../CPP_GameModeBase.h"
#include "../CPP_Character.h"

// Sets default values
ACPP_ActionVolume::ACPP_ActionVolume()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Create the Trigger Box Component
    TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
    RootComponent = TriggerBox;
    TriggerBox->SetCollisionProfileName(TEXT("Trigger"));

    // Set default action volume type
    VolumeType = EVolumeType::FallZone;

}

// Called when the game starts or when spawned
void ACPP_ActionVolume::BeginPlay()
{
    Super::BeginPlay();

    // Bind my custom function to trigger box on begin overlap event
    TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ACPP_ActionVolume::OnOverlapBegin);
}

void ACPP_ActionVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Check if the actor is valid and is the Player (ACharacter)
    if (IsValid(OtherActor) && OtherActor != this && OtherActor->IsA(ACPP_Character::StaticClass()))
    {
        // Decide what to do based on the Enum selection
        switch (VolumeType)
        {
        case EVolumeType::FallZone:
            Cast<ACPP_Character>(OtherActor)->onFallOutOfWorld.Broadcast();
            break;

        case EVolumeType::WinZone:
            Cast<ACPP_Character>(OtherActor)->onLevelComplete.Broadcast();
            break;

        case EVolumeType::UpdateSpawnPointZone:
			ACPP_GameModeBase* GM = Cast<ACPP_GameModeBase>(GetWorld()->GetAuthGameMode());
            if (IsValid(GM)) GM->UpdateRespawnPoint(GetActorLocation());
			break;
        }
    }
}

// Called every frame
void ACPP_ActionVolume::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

