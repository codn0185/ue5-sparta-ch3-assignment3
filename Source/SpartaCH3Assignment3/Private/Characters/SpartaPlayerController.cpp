#include "Characters/SpartaPlayerController.h"

#include "EnhancedInputSubsystems.h"

#include "Blueprint/UserWidget.h"
#include "Characters/SpartaCharacter.h"
#include "Components/Button.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Core/SpartaGameInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/GameHUD.h"

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

	// InputMappingContext 연결
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

	// EGameState 확인
	if (USpartaGameInstance* GameInstance = GetGameInstance<USpartaGameInstance>())
	{
		EGameState GameState = GameInstance->GetCurrentGameState();
		switch (GameState)
		{
			case EGameState::MainMenu:
				HideAllUI();
				ShowMainMenu();
				break;
			case EGameState::Playing:
				HideAllUI();
				ShowGameHUD();
				break;
		}
	}
}

void ASpartaPlayerController::HideAllUI()
{
	HideMainMenu();
	HideGameOver();
	HideGameClear();
	HideGameHUD();

	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
}

void ASpartaPlayerController::EnableUIInputMode()
{
	bShowMouseCursor = true;
	SetInputMode(FInputModeUIOnly());

	if (ACharacter* PlayerCharacter = GetCharacter())
	{
		PlayerCharacter->ConsumeMovementInputVector();
		if (UCharacterMovementComponent* MovementComponent = PlayerCharacter->GetCharacterMovement())
		{
			MovementComponent->StopMovementImmediately();
		}
	}
}

void ASpartaPlayerController::ShowMainMenu()
{
	UE_LOG(LogTemp, Warning, TEXT("ASpartaPlayerController::ShowMainMenu()"));

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

		EnableUIInputMode();
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
	UE_LOG(LogTemp, Warning, TEXT("ASpartaPlayerController::ShowGameOver()"));

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

		EnableUIInputMode();
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
	UE_LOG(LogTemp, Warning, TEXT("ASpartaPlayerController::ShowGameClear()"));

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

		EnableUIInputMode();
	}
}

void ASpartaPlayerController::HideGameClear()
{
	if (GameClearWidget)
	{
		GameClearWidget->RemoveFromParent();
	}
}

bool ASpartaPlayerController::InitializeGameHUD()
{
	if (GameHUDWidget)
	{
		return true;
	}

	if (!GameHUDWidgetClass)
	{
		return false;
	}

	GameHUDWidget = CreateWidget<UGameHUD>(this, GameHUDWidgetClass);
	return GameHUDWidget != nullptr;
}

void ASpartaPlayerController::ShowGameHUD()
{
	UE_LOG(LogTemp, Warning, TEXT("ASpartaPlayerController::ShowGameHUD()"));

	// GameHUDWidget 생성
	if (!InitializeGameHUD())
	{
		return;
	}

	// Viewport에 추가
	GameHUDWidget->AddToViewport();

	// 입력 모드 - Game
	bShowMouseCursor = false;
	SetInputMode(FInputModeGameOnly());
}

void ASpartaPlayerController::HideGameHUD()
{
	if (GameHUDWidget)
	{
		GameHUDWidget->RemoveFromParent();
	}
}

void ASpartaPlayerController::UpdateGameHUDStage(FName StageName, int32 StageNumber)
{
	if (!InitializeGameHUD())
	{
		return;
	}

	GameHUDWidget->SetStage(StageName, StageNumber);
}

void ASpartaPlayerController::UpdateGameHUDWave(int32 WaveNumber, int32 MaxWaveNumber)
{
	if (!InitializeGameHUD())
	{
		return;
	}

	GameHUDWidget->SetWave(WaveNumber, MaxWaveNumber);
}

void ASpartaPlayerController::UpdateGameHUDTime(float RemainingTime, float TotalTime)
{
	if (!InitializeGameHUD())
	{
		return;
	}

	GameHUDWidget->SetTime(RemainingTime, TotalTime);
}

void ASpartaPlayerController::UpdateGameHUDScore(int32 Score)
{
	if (!InitializeGameHUD())
	{
		return;
	}

	GameHUDWidget->SetScore(Score);
}

void ASpartaPlayerController::UpdateGameHUDCoin(int32 CollectedCoinCount, int32 TotalCoinCount)
{
	if (!InitializeGameHUD())
	{
		return;
	}

	GameHUDWidget->SetCoin(CollectedCoinCount, TotalCoinCount);
}

void ASpartaPlayerController::UpdateGameHUDHealth(int32 Health, int32 MaxHealth)
{
	if (InitializeGameHUD())
	{
		GameHUDWidget->SetHealth(Health, MaxHealth);
	}

	if (ASpartaCharacter* PlayerCharacter = GetPawn<ASpartaCharacter>())
	{
		PlayerCharacter->UpdateOverheadWidgetHealth();
	}
}

void ASpartaPlayerController::UpdateGameHUDEffect()
{
	if (!InitializeGameHUD())
	{
		return;
	}

	// TODO: 이펙트 UI 설정
}
