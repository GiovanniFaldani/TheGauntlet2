// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/Subsystems/CPP_QuestSubsystem.h"
#include "Engine/DataTable.h"

void UCPP_QuestSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

    const TCHAR* TablePath = TEXT("/Script/Engine.DataTable'/Game/_Game/Assets/DT_Quests.DT_Quests'");

    if (!QuestDataTable)
    {
        QuestDataTable = LoadObject<UDataTable>(nullptr, TablePath);
    }

    check(GEngine);
    if (QuestDataTable)
    {
        GEngine->AddOnScreenDebugMessage(15, 5.f, FColor::Blue , TEXT("Quest DataTable loaded successfully!"));
    }
    else
    {
        GEngine->AddOnScreenDebugMessage(15, 5.f, FColor::Red, FString::Printf(TEXT("ERROR: can't find DataTable at %s"), TablePath));
    }

}

void UCPP_QuestSubsystem::LoadQuestAssetsAsync(FName QuestID)
{
    if (!QuestDataTable) return;

 //   check(GEngine);
	//GEngine->AddOnScreenDebugMessage(16, 5.f, FColor::Green, FString::Printf(TEXT("Caricamento asset per la quest: %s"), *QuestID.ToString()));

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

FString UCPP_QuestSubsystem::GetQuestDescription(FName QuestID)
{
    static const FString ContextString(TEXT("HUDQuestContext"));
    if (QuestDataTable)
    {
        FQuestDetailsRow* Row = QuestDataTable->FindRow<FQuestDetailsRow>(QuestID, ContextString);
        if (Row)
        {
            return Row->QuestDescription.ToString();
        }
        else
        {
            return FString("Quest not found");
		}
	}
    else
    {
		return FString("Quest DataTable not loaded");
    }
}
