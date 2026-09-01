#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "StartGameButtonWidget.generated.h"

class UButton;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UStartGameButtonWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> StartGameButton;

	virtual void NativeConstruct() override;

  private:
	UFUNCTION()
	void OnClicked();
};
