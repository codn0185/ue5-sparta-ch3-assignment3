#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "MainMenuButtonWidget.generated.h"

class UButton;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UMainMenuButtonWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> MainMenuButton;

	virtual void NativeConstruct() override;

  private:
	UFUNCTION()
	void OnClicked();
};
