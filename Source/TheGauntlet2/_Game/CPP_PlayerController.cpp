// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/CPP_PlayerController.h"
#include "UI/CPP_HUDWidget.h"
#include "CPP_Character.h"
#include "Components/CPP_InteractionComponent.h"
#include "GameFramework/Character.h" 

void ACPP_PlayerController::BeginPlay()
{
	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UCPP_HUDWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			// Add HUD to viewport
			HUDWidgetInstance->AddToViewport();
			FInputModeGameOnly GameInputMode;
			SetInputMode(GameInputMode);
			bShowMouseCursor = false;
			PublishQuestDescription(FName("Quest01"));
		}
	}
}

void ACPP_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Add IMC BEFORE the character sets up input bindings
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (ACPP_Character* MyCharacter = Cast<ACPP_Character>(GetPawn()))
		{
			if (MyCharacter->GetInputMappingContext())
			{
				Subsystem->AddMappingContext(MyCharacter->GetInputMappingContext(), 0);
			}
		}
	}
}

// launches on Pawn posses (at level01 load in this case), use this to bind UI to player delegates
void ACPP_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	BindToPawnDelegates(InPawn);
}

void ACPP_PlayerController::BindToPawnDelegates(APawn* InPawn)
{
	ACPP_Character* MyPlayer = Cast<ACPP_Character>(InPawn);
	if (IsValid(MyPlayer))
	{
		// Unbind first to prevent double binding
		MyPlayer->onHealthChanged.RemoveDynamic(this, &ACPP_PlayerController::HandlePawnHealthChanged);

		// Bind	delegate
		MyPlayer->onHealthChanged.AddDynamic(this, &ACPP_PlayerController::HandlePawnHealthChanged);

		// bind interaction component delegate
		UCPP_InteractionComponent* InteractComponent = Cast<UCPP_InteractionComponent>(MyPlayer->GetComponentByClass(UCPP_InteractionComponent::StaticClass()));
		if (IsValid(InteractComponent))
		{
			InteractComponent->onFindInteractable.BindUObject(this, &ACPP_PlayerController::HandleInteractionMessage, true);
			InteractComponent->onLoseInteractable.BindUObject(this, &ACPP_PlayerController::HandleInteractionMessage, false);
		}
	}
}

void ACPP_PlayerController::HandlePawnHealthChanged(float NewHealth, float MaxHealth)
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->UpdateHealth(NewHealth, MaxHealth);
	}
}

void ACPP_PlayerController::HandleInteractionMessage(bool Found)
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->SetInteractionMessageVisibility(Found);
	}
}

void ACPP_PlayerController::TogglePauseMenu()
{
	if (IsPaused())
	{
		UnPause();
	}
	else
	{
		// PAUSE
		if (PauseWidgetClass)
		{
			//check(GEngine);
			//GEngine->AddOnScreenDebugMessage(5, 1.0f, FColor::Blue, TEXT("Paused"));

			PauseWidgetInstance = CreateWidget<UUserWidget>(this, PauseWidgetClass);
			if (PauseWidgetInstance)
			{
				PauseWidgetInstance->AddToViewport();
				bShowMouseCursor = true;

				FInputModeGameAndUI InputModeData;
				InputModeData.SetWidgetToFocus(PauseWidgetInstance->TakeWidget());
				InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
				SetInputMode(InputModeData);
				SetPause(true);
			}
		}
	}
}

void ACPP_PlayerController::UnPause()
{
	// RESUME
	//check(GEngine);
	//GEngine->AddOnScreenDebugMessage(5, 1.0f, FColor::Blue, TEXT("Unpaused"));

	SetPause(false);
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());

	if (PauseWidgetInstance) PauseWidgetInstance->RemoveFromParent();
}

void ACPP_PlayerController::PublishUIMessage(FString Message, float Duration)
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->DisplaySystemMessage(Message, Duration);
	}
}

void ACPP_PlayerController::PublishQuestDescription(FName QuestID)
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->UpdateQuestDescription(QuestID);
	}
}
