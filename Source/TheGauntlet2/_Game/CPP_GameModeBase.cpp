// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/CPP_GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "CPP_Character.h"
#include "CPP_PlayerController.h"

void ACPP_GameModeBase::BeginPlay()
{
	// Subscribe to player delegates
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (IsValid(PlayerController))
	{
		ACPP_Character* PlayerCharacter = Cast<ACPP_Character>(PlayerController->GetCharacter());
		if (IsValid(PlayerCharacter))
		{
			PlayerCharacter->onGameOver.AddUObject(this, &ACPP_GameModeBase::GameOver);
			PlayerCharacter->onFallOutOfWorld.AddUObject(this, &ACPP_GameModeBase::PlayerFell);
			PlayerCharacter->onLevelComplete.AddUObject(this, &ACPP_GameModeBase::GameVictory);
		}
	}

	GameInstanceRef = Cast<UCPP_GameInstance>(GetGameInstance());

}

void ACPP_GameModeBase::ShowEndGameWidget(TSubclassOf<UUserWidget> WidgetClass)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (IsValid(PlayerController))
	{
		// Create Widget
		UUserWidget* EndGameWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		if (EndGameWidget)
		{
			EndGameWidget->AddToViewport();

			// Set Input Mode to UI Only so the mouse appears
			FInputModeUIOnly InputMode;
			InputMode.SetWidgetToFocus(EndGameWidget->TakeWidget());
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);

			PlayerController->SetInputMode(InputMode);
			PlayerController->bShowMouseCursor = true;
		}
	}
}

void ACPP_GameModeBase::PlayerFell()
{
	// Player fell from map behavior, deal FallDamage via the IDamageable interface and respawn on PlayerStart

	// Get player 
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
	if (IsValid(PlayerController))
	{
		ACPP_Character* PlayerCharacter = Cast<ACPP_Character>(PlayerController->GetCharacter());
		if (IsValid(PlayerCharacter) && PlayerCharacter->GetClass()->ImplementsInterface(UDamageable::StaticClass()))
		{
			// Call IDamageable method
			IDamageable::Execute_ReceiveDamage(PlayerCharacter, FallDamage);

			// Respawn player on PlayerStart
			PlayerCharacter->SetActorLocation(RespawnPoint);
		}
	}
}

void ACPP_GameModeBase::GameVictory()
{
	// Freeze player
	ACPP_PlayerController* PlayerController = Cast<ACPP_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!IsValid(PlayerController)) return;

	PlayerController->PublishUIMessage(TEXT("Victory!"));
	PlayerController->SetIgnoreMoveInput(true);
	PlayerController->SetIgnoreLookInput(true);

	// Show the Victory Widget
	ShowEndGameWidget(VictoryWidgetClass);

	// Start timer to main menu
	if (IsValid(GameInstanceRef))
	{
		FTimerDelegate ToCall = FTimerDelegate::CreateUObject(GameInstanceRef, &UCPP_GameInstance::LoadLevel, FName("MainMenu"));
		GetWorld()->GetTimerManager().SetTimer(
			RestartTimer,
			ToCall,
			TimeUntilMainMenu,
			false
		);
	}
}

void ACPP_GameModeBase::GameOver()
{
	// Freeze player
	ACPP_PlayerController* PlayerController = Cast<ACPP_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	if (!IsValid(PlayerController)) return;

	PlayerController->PublishUIMessage(TEXT("Game Over!"));
	PlayerController->SetIgnoreMoveInput(true);
	PlayerController->SetIgnoreLookInput(true);

	// Show the Game Over Widget
	ShowEndGameWidget(GameOverWidgetClass);

	// Start timer to main menu
	if (IsValid(GameInstanceRef))
	{
		FTimerDelegate ToCall = FTimerDelegate::CreateUObject(GameInstanceRef, &UCPP_GameInstance::LoadLevel, FName("MainMenu"));
		GetWorld()->GetTimerManager().SetTimer(
			RestartTimer,
			ToCall,
			TimeUntilMainMenu,
			false
		);
	}
}