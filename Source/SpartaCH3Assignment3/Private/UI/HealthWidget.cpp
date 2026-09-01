#include "UI/HealthWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UHealthWidget::SetHealth(int32 Health, int32 MaxHealth)
{
	if (HealthText)
	{
		HealthText->SetText(FText::AsNumber(Health));
	}

	if (MaxHealthText)
	{
		MaxHealthText->SetText(FText::AsNumber(MaxHealth));
	}

	if (HealthProgressBar)
	{
		const float HealthPercentage = MaxHealth > 0
										   ? FMath::Clamp(1.f * Health / MaxHealth, 0.f, 1.f)
										   : 0.f;
		HealthProgressBar->SetPercent(HealthPercentage);
	}
}
