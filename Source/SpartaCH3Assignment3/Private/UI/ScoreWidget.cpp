#include "UI/ScoreWidget.h"

#include "Components/TextBlock.h"

void UScoreWidget::SetScore(int32 Score)
{
	if (ScoreText)
	{
		ScoreText->SetText(FText::AsNumber(Score));
	}
}
