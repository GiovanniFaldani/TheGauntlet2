// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Blueprint/UserWidget.h"
#include "CPP_PlayerController.generated.h"

class UCPP_HUDWidget;

/**
 *
 */
UCLASS()
class THEGAUNTLET2_API ACPP_PlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	// The class of the HUD to spawn
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UCPP_HUDWidget> HUDWidgetClass;

	// The actual instance of the HUD
	UPROPERTY()
	TObjectPtr<UCPP_HUDWidget> HUDWidgetInstance;

	// same but for pause menu
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY()
	TObjectPtr<UUserWidget> PauseWidgetInstance;

public:
	// Print message to screen from anywhere
	UFUNCTION(BlueprintCallable, Category = "UI")
	void PublishUIMessage(FString Message);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void TogglePauseMenu();

	void UnPause();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	// Helper to bind to the Pawn's delegates
	void BindToPawnDelegates(APawn* InPawn);

	// Callback when the Pawn broadcasts a health change
	UFUNCTION()
	void HandlePawnHealthChanged(float NewHealth, float MaxHealth);

	// Callback when the Pawn broadcasts interactable actor found
	UFUNCTION()
	void HandleInteractionMessage(bool Found);
};