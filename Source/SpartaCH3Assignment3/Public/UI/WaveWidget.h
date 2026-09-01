#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "WaveWidget.generated.h"

class UTextBlock;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UWaveWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> WaveNumberText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxWaveNumberText;

  public:
	void SetWave(int32 WaveNumber, int32 MaxWaveNumber);
};
