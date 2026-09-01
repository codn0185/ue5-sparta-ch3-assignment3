#include "UI/WaveWidget.h"

#include "Components/TextBlock.h"

void UWaveWidget::SetWave(int32 WaveNumber, int32 MaxWaveNumber)
{
	if (WaveNumberText)
	{
		WaveNumberText->SetText(FText::AsNumber(WaveNumber));
	}

	if (MaxWaveNumberText)
	{
		MaxWaveNumberText->SetText(FText::AsNumber(MaxWaveNumber));
	}
}
