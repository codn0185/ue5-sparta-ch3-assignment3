#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "MainMenu.generated.h"

class UUserWidget;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> StartGameButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> ShowLeaderboardButton;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UUserWidget> ExitGameButton;
};
