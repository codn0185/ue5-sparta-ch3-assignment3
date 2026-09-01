#include "UI/CoinWidget.h"

#include "Components/TextBlock.h"

void UCoinWidget::SetCoin(int32 CollectedCoinCount, int32 TotalCoinCount)
{
	if (CollectedCoinCountText)
	{
		CollectedCoinCountText->SetText(FText::AsNumber(CollectedCoinCount));
	}

	if (TotalCoinCountText)
	{
		TotalCoinCountText->SetText(FText::AsNumber(TotalCoinCount));
	}
}
