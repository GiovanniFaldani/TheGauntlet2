// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonActivatableWidget.h"
#include "../Subsystems/CPP_QuestSubsystem.h"
#include "../Data/CPP_QuestAssets.h"

#include "CPP_HUDWidget.generated.h"

class UCommonTextBlock;
class UProgressBar;

/**
 *
 */
UCLASS()
class THEGAUNTLET2_API UCPP_HUDWidget : public UCommonActivatableWidget
{
	GENERATED_BODY()

protected:
	// These names MUST match the names in the Widget Blueprint exactly!

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> SystemMessageText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> InteractionPromptText;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	TObjectPtr<UCommonTextBlock> QuestDescriptionText;


protected:
	virtual void NativeConstruct() override;

public:

	// Update health display
	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateHealth(float CurrentHealth, float MaxHealth);

	// Post message to screen
	UFUNCTION(BlueprintCallable, Category = "UI")
	void DisplaySystemMessage(FString Message, float Duration = 3.f);

	// Interaction prompt
	UFUNCTION(BlueprintCallable, Category = "UI")
	void SetInteractionMessageVisibility(bool Visible);

	UFUNCTION(BlueprintCallable, Category = "UI")
	void UpdateQuestDescription(FName QuestID);

private:
	FTimerHandle SystemMessageTimerHandle;

	void ClearSystemMessage();

};
