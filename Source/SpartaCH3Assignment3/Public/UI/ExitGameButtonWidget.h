#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "ExitGameButtonWidget.generated.h"

class UButton;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UExitGameButtonWidget : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> ExitGameButton;

	virtual void NativeConstruct() override;

  private:
	UFUNCTION()
	void OnClicked();
};
