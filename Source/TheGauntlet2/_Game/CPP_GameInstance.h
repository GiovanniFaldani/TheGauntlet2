// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CPP_GameInstance.generated.h"

/**
 *
 */
UCLASS()
class THEGAUNTLET2_API UCPP_GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = LevelControl)
	void LoadLevel(FName LevelName);

	UFUNCTION(BlueprintCallable, Category = LevelControl)
	void QuitGame();

};
