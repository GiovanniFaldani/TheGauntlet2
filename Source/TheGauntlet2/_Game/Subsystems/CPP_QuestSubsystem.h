// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/StreamableManager.h"
#include "CPP_QuestSubsystem.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnQuestAssetsLoaded, UNiagaraSystem*, VFX, USoundBase*, SFX);

UCLASS()
class THEGAUNTLET2_API UCPP_QuestSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
    // Delegato per utilizzare gli asset quando sono pronti
    FOnQuestAssetsLoaded onQuestAssetsReady;

    virtual void Initialize(FSubsystemCollectionBase& Collection) override;

    UFUNCTION(BlueprintCallable, Category = "Quest")
    void LoadQuestAssetsAsync(FName QuestID);

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Quest")
    UDataTable* QuestDataTable;

    FStreamableManager StreamableManager;
    TSharedPtr<FStreamableHandle> AssetHandle;

    void OnAssetsLoaded(TSoftObjectPtr<UNiagaraSystem> VfxPtr, TSoftObjectPtr<USoundBase> SfxPtr);

    void CompleteQuest();
};
