
#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "ShowLeaderboardButtonWidget.generated.h"

class UButton;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UShowLeaderboardButtonWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ShowLeaderboardButton;

	virtual void NativeConstruct() override;

  private:
	UFUNCTION()
	void OnClicked();
};
