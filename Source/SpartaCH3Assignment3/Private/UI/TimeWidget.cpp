#include "UI/TimeWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UTimeWidget::SetTime(float RemainingTime, float TotalTime)
{
	if (RemainingTimeText)
	{
		RemainingTimeText->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), RemainingTime)));
	}

	if (TimeProgressBar)
	{
		const float TimePercentage = TotalTime > 0.f
										 ? FMath::Clamp(RemainingTime / TotalTime, 0.f, 1.f)
										 : 0.f;
		TimeProgressBar->SetPercent(TimePercentage);
	}
}
