#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "ScoreWidget.generated.h"

class UTextBlock;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UScoreWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> ScoreText;

  public:
	void SetScore(int32 Score);
};
