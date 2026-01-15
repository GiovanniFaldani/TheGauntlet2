// Fill out your copyright notice in the Description page of Project Settings.


#include "_Game/UI/CPP_HUDWidget.h"
#include "CommonTextBlock.h"
#include "Components/ProgressBar.h"

void UCPP_HUDWidget::NativeConstruct()
{
	if (SystemMessageText)
	{
		SystemMessageText->SetText(FText::GetEmpty());
		SystemMessageText->SetVisibility(ESlateVisibility::Hidden);
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

void UCPP_HUDWidget::DisplaySystemMessage(FString Message, float Duration)
{
	if (SystemMessageText)
	{
		SystemMessageText->SetText(FText::FromString(Message));
		SystemMessageText->SetVisibility(ESlateVisibility::Visible);

	}

	if (GetWorld()->GetTimerManager().IsTimerActive(SystemMessageTimerHandle))
	{
		// clear timer in case new message is pushed before old one is cleared
		GetWorld()->GetTimerManager().ClearTimer(SystemMessageTimerHandle);
	}


	GetWorld()->GetTimerManager().SetTimer(
		SystemMessageTimerHandle,
		this,
		&UCPP_HUDWidget::ClearSystemMessage,
		Duration,
		false
	);
}

void UCPP_HUDWidget::SetInteractionMessageVisibility(bool Visible)
{
	InteractionPromptText->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UCPP_HUDWidget::UpdateQuestDescription(FName QuestID)
{
	if (!QuestDescriptionText) return;

	UGameInstance* GI = GetGameInstance();
	if (!GI) return;

	UCPP_QuestSubsystem* QuestSub = GI->GetSubsystem<UCPP_QuestSubsystem>();

	if (QuestSub)
	{
		QuestDescriptionText->SetText(FText::FromString(QuestSub->GetQuestDescription(QuestID)));
	}
}

void UCPP_HUDWidget::ClearSystemMessage()
{
	if (SystemMessageText)
	{
		SystemMessageText->SetText(FText::GetEmpty());
		SystemMessageText->SetVisibility(ESlateVisibility::Hidden);
	}
}


