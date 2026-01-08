// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Actors/CPP_ExitAltar.h"

// Sets default values
ACPP_ExitAltar::ACPP_ExitAltar()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	ArtifactSocket = CreateDefaultSubobject<USceneComponent>(TEXT("ArtifactSocket"));
	ArtifactSocket->SetupAttachment(RootComponent);
	ArtifactSocket->SetRelativeLocation(FVector(0.f, 0.f, 100.f));
}

// Called when the game starts or when spawned
void ACPP_ExitAltar::BeginPlay()
{
	Super::BeginPlay();

	// set color
	if (Mesh && Mesh->GetMaterial(0))
	{
		// Init dynamic material based on static material assigned in editor
		DynamicMat = UMaterialInstanceDynamic::Create(Mesh->GetMaterial(0), this);

		UpdateColor(FColor::Purple);
	}
	
}

// Called every frame
void ACPP_ExitAltar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPP_ExitAltar::Interact_Implementation(AActor* Interacter)
{
	// check that Interacter is Player class
	ACPP_Character* Player = Cast<ACPP_Character>(Interacter);
	if (!Player) return;

	// check that player has artifact
	if (!Player->IsArtifactCollected() || !IsValid(Player->GetArtifactRef()))
	{
		// TODO write to hud that artifact is missing
		check(GEngine);
		GEngine->AddOnScreenDebugMessage(8, 5.f, FColor::Red, TEXT("You need to collect the artifact before exiting the level!"));
		return;
	}

	UGameInstance* GI = GetGameInstance();
	if (!GI) return;

	UCPP_QuestSubsystem* QuestSub = GI->GetSubsystem<UCPP_QuestSubsystem>();
	if (!QuestSub) return;

	UpdateColor(FColor::Green);

	// move artifact
	AActor* Artifact = Player->GetArtifactRef();
	Artifact->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
	Artifact->AttachToComponent(ArtifactSocket, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	Player->SetArtifactCollected(false, nullptr);

	// trigger level complete events

	QuestSub->onQuestAssetsReady.AddDynamic(this, &ACPP_ExitAltar::OnVictoryAssetsLoaded);
	QuestSub->LoadQuestAssetsAsync(QuestID);
	Player->onLevelComplete.Broadcast();
}

USceneComponent* ACPP_ExitAltar::GetArtifactSocket()
{
	return ArtifactSocket;
}

void ACPP_ExitAltar::OnVictoryAssetsLoaded(UNiagaraSystem* VFX, USoundBase* SFX)
{
	if (VFX) UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), VFX, GetActorLocation(), GetActorRotation(), FVector(1.f), true);
	if (SFX) UGameplayStatics::PlaySoundAtLocation(GetWorld(), SFX, GetActorLocation());
}

void ACPP_ExitAltar::UpdateColor(FColor NewColor)
{
	if (DynamicMat)
	{
		DynamicMat->SetVectorParameterValue(TEXT("Color"), NewColor);
		Mesh->SetMaterial(0, DynamicMat);
	}
}

