#include "Characters/SpartaPlayerController.h"

#include "EnhancedInputSubsystems.h"

#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

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

void ASpartaPlayerController::UpdateGameHUDStage(FName StageName, int32 StageNumber)
{
	if (!GameHUDWidget)
	{
		return;
	}

	if (UTextBlock* StageNameText = Cast<UTextBlock>(GameHUDWidget->GetWidgetFromName(StageNameTextWidgetName)))
	{
		StageNameText->SetText(FText::FromName(StageName));
	}
	if (UTextBlock* StageNumberText = Cast<UTextBlock>(GameHUDWidget->GetWidgetFromName(StageNumberTextWidgetName)))
	{
		StageNumberText->SetText(FText::AsNumber(StageNumber));
	}
}

void ASpartaPlayerController::UpdateGameHUDWave(int32 WaveNumber, int32 MaxWaveNumber)
{
	if (!GameHUDWidget)
	{
		return;
	}

	if (UTextBlock* WaveNumberText = Cast<UTextBlock>(GameHUDWidget->GetWidgetFromName(WaveNumberTextWidgetName)))
	{
		WaveNumberText->SetText(FText::AsNumber(WaveNumber));
	}
	if (UTextBlock* MaxWaveNumberText = Cast<UTextBlock>(GameHUDWidget->GetWidgetFromName(MaxWaveNumberTextWidgetName)))
	{
		MaxWaveNumberText->SetText(FText::AsNumber(MaxWaveNumber));
	}
}

void ASpartaPlayerController::UpdateGameHUDTime(float RemainingTime, float TotalTime)
{
	if (!GameHUDWidget)
	{
		return;
	}

	if (UTextBlock* RemainingTimeText = Cast<UTextBlock>(GameHUDWidget->GetWidgetFromName(RemainingTimeTextWidgetName)))
	{
		RemainingTimeText->SetText(FText::FromString(FString::Printf(TEXT("%.1f"), RemainingTime)));
	}
	if (UProgressBar* TimeProgressBar = Cast<UProgressBar>(GameHUDWidget->GetWidgetFromName(TimeProgressBarWidgetName)))
	{
		const float TimePercentage = TotalTime > 0.f
										 ? FMath::Clamp(RemainingTime / TotalTime, 0.f, 1.f)
										 : 0.f;
		TimeProgressBar->SetPercent(TimePercentage);
	}
}

void ASpartaPlayerController::UpdateGameHUDScore(int32 Score)
{
	if (!GameHUDWidget)
	{
		return;
	}

	if (UTextBlock* ScoreText = Cast<UTextBlock>(GameHUDWidget->GetWidgetFromName(ScoreTextWidgetName)))
	{
		ScoreText->SetText(FText::AsNumber(Score));
	}
}

void ASpartaPlayerController::UpdateGameHUDCoin(int32 CollectedCoinCount, int32 TotalCoinCount)
{
	if (!GameHUDWidget)
	{
		return;
	}

	if (UTextBlock* CollectedCoinCountText = Cast<UTextBlock>(GameHUDWidget->GetWidgetFromName(CollectedCoinCountTextWidgetName)))
	{
		CollectedCoinCountText->SetText(FText::AsNumber(CollectedCoinCount));
	}
	if (UTextBlock* TotalCoinCountText = Cast<UTextBlock>(GameHUDWidget->GetWidgetFromName(TotalCoinCountTextWidgetName)))
	{
		TotalCoinCountText->SetText(FText::AsNumber(TotalCoinCount));
	}
}

void ASpartaPlayerController::UpdateGameHUDHealth(int32 Health, int32 MaxHealth)
{
	if (!GameHUDWidget)
	{
		return;
	}

	if (UTextBlock* HealthText = Cast<UTextBlock>(GameHUDWidget->GetWidgetFromName(HealthTextWidgetName)))
	{
		HealthText->SetText(FText::AsNumber(Health));
	}
	if (UTextBlock* MaxHealthText = Cast<UTextBlock>(GameHUDWidget->GetWidgetFromName(MaxHealthTextWidgetName)))
	{
		MaxHealthText->SetText(FText::AsNumber(MaxHealth));
	}
	if (UProgressBar* HealthProgressBar = Cast<UProgressBar>(GameHUDWidget->GetWidgetFromName(HealthProgressBarWidgetName)))
	{
		const float HealthPercentage = MaxHealth > 0
										   ? FMath::Clamp(1.f * Health / MaxHealth, 0.f, 1.f)
										   : 0.f;
		HealthProgressBar->SetPercent(HealthPercentage);
	}
}

void ASpartaPlayerController::UpdateGameHUDEffect()
{
	if (!GameHUDWidget)
	{
		return;
	}

	// TODO: 이펙트 UI 설정
}
