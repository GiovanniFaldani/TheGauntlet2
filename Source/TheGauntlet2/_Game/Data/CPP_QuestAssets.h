// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NiagaraSystem.h"
#include "CPP_QuestAssets.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FQuestDetailsRow : public FTableRowBase
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText QuestName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    FText QuestDescription;

    UPROPERTY(EditAnywhere, BlueprintReadOnly)
    UCPP_QuestAssets* QuestAssets;
};

UCLASS()
class THEGAUNTLET2_API UCPP_QuestAssets : public UDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Assets")
	TSoftObjectPtr<UNiagaraSystem> VictoryVFX;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest Assets")
	TSoftObjectPtr<USoundBase> VictorySound;
};
