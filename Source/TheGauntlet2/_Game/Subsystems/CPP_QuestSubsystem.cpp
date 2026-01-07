// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Subsystems/CPP_QuestSubsystem.h"
#include "Engine/DataTable.h"
#include "../Data/CPP_QuestAssets.h"

void UCPP_QuestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

}

void UCPP_QuestSubsystem::LoadQuestAssetsAsync(FName QuestID)
{
    if (!QuestDataTable) return;

    static const FString ContextString(TEXT("QuestContext"));
    FQuestDetailsRow* Row = QuestDataTable->FindRow<FQuestDetailsRow>(QuestID, ContextString);

    if (Row && Row->QuestAssets)
    {
        TArray<FSoftObjectPath> AssetsToLoad;

        AssetsToLoad.Add(Row->QuestAssets->VictoryVFX.ToSoftObjectPath());
        AssetsToLoad.Add(Row->QuestAssets->VictorySound.ToSoftObjectPath());

        // caricamento asincrono
        AssetHandle = StreamableManager.RequestAsyncLoad(AssetsToLoad,
            FStreamableDelegate::CreateUObject(this, &UCPP_QuestSubsystem::OnAssetsLoaded, Row->QuestAssets->VictoryVFX, Row->QuestAssets->VictorySound)
        );
    }
}

void UCPP_QuestSubsystem::OnAssetsLoaded(TSoftObjectPtr<UNiagaraSystem> VfxPtr, TSoftObjectPtr<USoundBase> SfxPtr)
{
    // Puntatori pronti ad essere usati dal delegate
    if (UNiagaraSystem* LoadedVFX = VfxPtr.Get())
    {
        if (USoundBase* LoadedSFX = SfxPtr.Get())
        {
            onQuestAssetsReady.Broadcast(LoadedVFX, LoadedSFX);
        }
    }
}
