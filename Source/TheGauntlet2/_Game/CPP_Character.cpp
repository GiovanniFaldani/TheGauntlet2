// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/CPP_Character.h"

// Sets default values
ACPP_Character::ACPP_Character()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Set up camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	Arm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	Arm->SetupAttachment(RootComponent);
	Arm->TargetArmLength = CameraDistance;
	Arm->SetRelativeRotation(FRotator(-45.f, 0.f, 0.f));

	// tweak if necessary
	Arm->bEnableCameraLag = false;
	Arm->CameraLagSpeed = 2;
	Arm->CameraLagMaxDistance = 1.5f;

	Arm->bEnableCameraRotationLag = false;
	Arm->CameraRotationLagSpeed = 4;
	Arm->CameraLagMaxTimeStep = 1;

	Camera->SetupAttachment(Arm, USpringArmComponent::SocketName);

	// Set up interaction component
	InteractionComponent = CreateDefaultSubobject<UCPP_InteractionComponent>(TEXT("Interaction"));

	// setup artifact socket
	ArtifactSocket = CreateDefaultSubobject<USceneComponent>(TEXT("ArtifactSocket"));
	ArtifactSocket->SetupAttachment(RootComponent);
	ArtifactSocket->SetRelativeLocation(FVector(50.f, 50.f, 100.f));
}

// Called when the game starts or when spawned
void ACPP_Character::BeginPlay()
{
	Super::BeginPlay();

	// Set health variable
	HP = MaxHP;

	// Get the player controller for this character
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		// Get the enhanced input local player subsystem and add a new input mapping context to it
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMappingContext, 0);
			FInputModeGameOnly InputModeData;
			PlayerController->SetInputMode(InputModeData);
			PlayerController->bShowMouseCursor = false;
		}
	}

	// Fill health bar
	onHealthChanged.Broadcast(HP, MaxHP);
}

// Called every frame
void ACPP_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Count down interaction timer if active
	if (InteractTimer >= 0)
	{
		InteractTimer -= DeltaTime;
		if (InteractTimer <= 0)
		{
			CanInteract = true;
		}
	}

}

// Called to bind functionality to input
void ACPP_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	// Check the UInputComponent passed to this function and cast it to an UEnhancedInputComponent
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Bind Movement Actions
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACPP_Character::Move);

		// Bind Camera Actions
		EnhancedInputComponent->BindAction(CameraAction, ETriggerEvent::Triggered, this, &ACPP_Character::MoveCamera);

		// Bind Jump Actions
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Bind Interact Action
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &ACPP_Character::OnInteract);
	}

}

void ACPP_Character::Move(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Forward = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// Add wasd movement
		AddMovementInput(Right, MovementValue.X);
		AddMovementInput(Forward, MovementValue.Y);

	}
}

void ACPP_Character::MoveCamera(const FInputActionValue& Value)
{
	const FVector2D MovementValue = Value.Get<FVector2D>();

	if (IsValid(Controller))
	{
		// Camera pitch and yaw
		AddControllerYawInput(-MovementValue.X);
		AddControllerPitchInput(MovementValue.Y);
	}
}

void ACPP_Character::OnInteract()
{
	if (!CanInteract) return;
	check(GEngine);
	GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Blue, TEXT("Interacted"));

	// Get ClosestActor from InteractionComponent and call Interact() on it.
	if (IsValid(InteractionComponent->ClosestActor) && InteractionComponent->ClosestActor->GetClass()->ImplementsInterface(UInteractable::StaticClass()))
	{
		// GEngine->AddOnScreenDebugMessage(11, 1.0f, FColor::Red, TEXT("Found interactable!"));
		IInteractable::Execute_Interact(InteractionComponent->ClosestActor, this);
	}

	// Start timer to limit number of interactions per second
	InteractTimer = InteractCooldown;
	CanInteract = false;

}

void ACPP_Character::ReceiveDamage_Implementation(float DamageReceived)
{
	HP -= DamageReceived;
	onHealthChanged.Broadcast(HP, MaxHP);
	if (HP <= .0f)
	{
		onGameOver.Broadcast();
	}
}

void ACPP_Character::SetKeyCollected(bool Value)
{
	// TODO artifact collection and use logic
	bHasArtifact = Value;
}

float ACPP_Character::GetMaxHP()
{
	return MaxHP;
}

float ACPP_Character::GetCurrentHP()
{
	return HP;
}

float ACPP_Character::GetDamage()
{
	return DamageDealt;
}