#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "HealthWidget.generated.h"

class UTextBlock;
class UProgressBar;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UHealthWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> HealthText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> MaxHealthText;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UProgressBar> HealthProgressBar;

  public:
	void SetHealth(int32 Health, int32 MaxHealth);
};
