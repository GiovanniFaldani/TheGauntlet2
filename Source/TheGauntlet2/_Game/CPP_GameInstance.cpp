// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/CPP_GameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UCPP_GameInstance::LoadLevel(FName LevelName)
{
	UWorld* const World = GetWorld();
	UGameplayStatics::OpenLevel(World, LevelName);

}

void UCPP_GameInstance::QuitGame()
{
	UWorld* const World = GetWorld();
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(World, 0);
	UKismetSystemLibrary::QuitGame(World, PlayerController, EQuitPreference::Quit, false);
}
