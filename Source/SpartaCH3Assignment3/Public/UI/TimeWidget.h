#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "TimeWidget.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UTimeWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> RemainingTimeText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> TimeProgressBar;

  public:
	void SetTime(float RemainingTime, float TotalTime);
};
