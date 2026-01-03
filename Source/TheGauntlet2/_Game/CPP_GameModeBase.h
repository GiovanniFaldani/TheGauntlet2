// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CPP_GameInstance.h"
#include "CPP_GameModeBase.generated.h"

/**
 *
 */
UCLASS()
class THEGAUNTLET2_API ACPP_GameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Mode")
	float FallDamage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Mode")
	float TimeUntilMainMenu;

	// Restart timer
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Mode")
	FTimerHandle RestartTimer;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Game Mode")
	FVector RespawnPoint;

	// Game Over screens
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Mode")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Game Mode")
	TSubclassOf<UUserWidget> VictoryWidgetClass;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Game Mode")
	UCPP_GameInstance* GameInstanceRef;

protected:
	virtual void BeginPlay() override;

	// Helper to spawn UI and set input mode
	void ShowEndGameWidget(TSubclassOf<UUserWidget> WidgetClass);

public:
	void PlayerFell();

	void GameVictory();

	void GameOver();
};