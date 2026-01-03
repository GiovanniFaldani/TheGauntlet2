// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/UI/CPP_HUDWidget.h"
#include "CommonTextBlock.h"
#include "Components/ProgressBar.h"

void UCPP_HUDWidget::NativeConstruct()
{
	if (SystemMessageText)
	{
		SystemMessageText->SetText(FText::GetEmpty());
	}
}

void UCPP_HUDWidget::UpdateHealth(float CurrentHealth, float MaxHealth)
{
	// Update Health Bar
	if (HealthProgressBar && MaxHealth > 0.0f)
	{
		const float Percent = FMath::Clamp(CurrentHealth / MaxHealth, 0.0f, 1.0f);
		HealthProgressBar->SetPercent(Percent);
	}
}

void UCPP_HUDWidget::DisplaySystemMessage(FString Message)
{
	if (SystemMessageText)
	{
		SystemMessageText->SetText(FText::FromString(Message));
	}
}

void UCPP_HUDWidget::SetInteractionMessageVisibility(bool Visible)
{
	InteractionPromptText->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}


