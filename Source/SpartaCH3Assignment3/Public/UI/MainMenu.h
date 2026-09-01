#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "MainMenu.generated.h"

class UStartGameButtonWidget;
class UShowLeaderboardButtonWidget;
class UExitGameButtonWidget;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UStartGameButtonWidget> StartGameButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UShowLeaderboardButtonWidget> ShowLeaderboardButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UExitGameButtonWidget> ExitGameButton;
};
