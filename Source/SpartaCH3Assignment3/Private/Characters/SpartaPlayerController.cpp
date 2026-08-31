#include "Characters/SpartaPlayerController.h"

#include "EnhancedInputSubsystems.h"

#include "Blueprint/UserWidget.h"

ASpartaPlayerController::ASpartaPlayerController()
	:  // IMC & IA
	  CharacterInputMappingContext(nullptr),
	  MoveAction(nullptr),
	  LookAction(nullptr),
	  JumpAction(nullptr),
	  SprintAction(nullptr),
	  // UI
	  MainMenuWidgetClass(nullptr),
	  MainMenuWidget(nullptr),
	  GameOverWidgetClass(nullptr),
	  GameOverWidget(nullptr),
	  GameClearWidgetClass(nullptr),
	  GameClearWidget(nullptr),
	  GameHUDWidgetClass(nullptr),
	  GameHUDWidget(nullptr)
{
}

void ASpartaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (CharacterInputMappingContext)
			{
				Subsystem->AddMappingContext(CharacterInputMappingContext, 0);
			}
		}
	}
}

void ASpartaPlayerController::ShowMainMenu()
{
	// MainMenuWidget 생성
	if (!MainMenuWidget)
	{
		if (MainMenuWidgetClass)
		{
			MainMenuWidget = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		}
	}

	// Viewport에 추가
	if (MainMenuWidget)
	{
		MainMenuWidget->AddToViewport();

		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}

void ASpartaPlayerController::HideMainMenu()
{
	if (MainMenuWidget)
	{
		MainMenuWidget->RemoveFromParent();
	}
}

void ASpartaPlayerController::ShowGameOver()
{
	// GameOverWidget 생성
	if (!GameOverWidget)
	{
		if (GameOverWidgetClass)
		{
			GameOverWidget = CreateWidget<UUserWidget>(this, GameOverWidgetClass);
		}
	}

	// Viewport에 추가
	if (GameOverWidget)
	{
		GameOverWidget->AddToViewport();

		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}

void ASpartaPlayerController::HideGameOver()
{
	if (GameOverWidget)
	{
		GameOverWidget->RemoveFromParent();
	}
}

void ASpartaPlayerController::ShowGameClear()
{
	// GameClearWidget 생성
	if (!GameClearWidget)
	{
		if (GameClearWidgetClass)
		{
			GameClearWidget = CreateWidget<UUserWidget>(this, GameClearWidgetClass);
		}
	}

	// Viewport에 추가
	if (GameClearWidget)
	{
		GameClearWidget->AddToViewport();

		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly());
	}
}

void ASpartaPlayerController::HideGameClear()
{
	if (GameClearWidget)
	{
		GameClearWidget->RemoveFromParent();
	}
}

void ASpartaPlayerController::ShowGameHUD()
{
	// GameHUDWidget 생성
	if (!GameHUDWidget)
	{
		if (GameHUDWidgetClass)
		{
			GameHUDWidget = CreateWidget<UUserWidget>(this, GameHUDWidgetClass);
		}
	}

	// Viewport에 추가
	if (GameHUDWidget)
	{
		GameHUDWidget->AddToViewport();

		bShowMouseCursor = false;
		SetInputMode(FInputModeGameOnly());
	}
}

void ASpartaPlayerController::HideGameHUD()
{
	if (GameHUDWidget)
	{
		GameHUDWidget->RemoveFromParent();
	}
}
