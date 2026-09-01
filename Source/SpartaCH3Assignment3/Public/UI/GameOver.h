#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "GameOver.generated.h"

class UUserWidget;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UGameOver : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> RestartGameButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> MainMenuButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> ExitGameButton;
};
