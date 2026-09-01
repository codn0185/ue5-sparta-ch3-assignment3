#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "CoinWidget.generated.h"

class UTextBlock;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UCoinWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> CollectedCoinCountText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TotalCoinCountText;

  public:
	void SetCoin(int32 CollectedCoinCount, int32 TotalCoinCount);
};
