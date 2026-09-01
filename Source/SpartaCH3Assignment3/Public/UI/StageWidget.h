#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "StageWidget.generated.h"

class UTextBlock;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UStageWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StageNameText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> StageNumberText;

  public:
	void SetStage(FName StageName, int32 StageNumber);
};
