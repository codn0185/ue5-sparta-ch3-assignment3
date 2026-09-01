#include "UI/StageWidget.h"

#include "Components/TextBlock.h"

void UStageWidget::SetStage(FName StageName, int32 StageNumber)
{
	if (StageNameText)
	{
		StageNameText->SetText(FText::FromName(StageName));
	}

	if (StageNumberText)
	{
		StageNumberText->SetText(FText::AsNumber(StageNumber));
	}
}
