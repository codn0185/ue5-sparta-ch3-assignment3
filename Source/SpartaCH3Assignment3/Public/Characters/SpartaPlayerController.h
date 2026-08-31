#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "SpartaPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;

class UUserWidget;

UCLASS()
class SPARTACH3ASSIGNMENT3_API ASpartaPlayerController : public APlayerController
{
	GENERATED_BODY()

  public:
	ASpartaPlayerController();

	// InputMappingContext & InputAction
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs|InputMappingContext")
	TObjectPtr<UInputMappingContext> CharacterInputMappingContext;  // IMC_Character
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs|InputAction")
	TObjectPtr<UInputAction> MoveAction;  // IA_Move
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs|InputAction")
	TObjectPtr<UInputAction> LookAction;  // IA_Look
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs|InputAction")
	TObjectPtr<UInputAction> JumpAction;  // IA_Jump
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Inputs|InputAction")
	TObjectPtr<UInputAction> SprintAction;  // IA_Sprint

  protected:
	// UI - MainMenu
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|MainMenu")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|MainMenu")
	UUserWidget* MainMenuWidget;

	// UI - GameOver
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|GameOver")
	TSubclassOf<UUserWidget> GameOverWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|GameOver")
	UUserWidget* GameOverWidget;

	// UI - GameClear
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|GameClear")
	TSubclassOf<UUserWidget> GameClearWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|GameClear")
	UUserWidget* GameClearWidget;

	// UI - GameHUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|GameHUD")
	TSubclassOf<UUserWidget> GameHUDWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|GameHUD")
	UUserWidget* GameHUDWidget;

	// GameHUD Widgets
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|GameHUD|Widgets|Stage")
	FName StageNameTextWidgetName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|GameHUD|Widgets|Stage")
	FName StageNumberTextWidgetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|GameHUD|Widgets|Wave")
	FName WaveNumberTextWidgetName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|GameHUD|Widgets|Wave")
	FName MaxWaveNumberTextWidgetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|GameHUD|Widgets|Time")
	FName RemainingTimeTextWidgetName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|GameHUD|Widgets|Time")
	FName TimeProgressBarWidgetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|GameHUD|Widgets|Score")
	FName ScoreTextWidgetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|GameHUD|Widgets|Coin")
	FName CollectedCoinCountTextWidgetName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|GameHUD|Widgets|Coin")
	FName TotalCoinCountTextWidgetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|GameHUD|Widgets|Health")
	FName HealthTextWidgetName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|GameHUD|Widgets|Health")
	FName MaxHealthTextWidgetName;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI|GameHUD|Widgets|Health")
	FName HealthProgressBarWidgetName;

  protected:
	virtual void BeginPlay() override;

  public:
	  // UI
	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideAllUI();

	// UI - MainMenu
	UFUNCTION(BlueprintCallable, Category = "UI|MainMenu")
	void ShowMainMenu();
	UFUNCTION(BlueprintCallable, Category = "UI|MainMenu")
	void HideMainMenu();

	// UI - GameOver
	UFUNCTION(BlueprintCallable, Category = "UI|GameOver")
	void ShowGameOver();
	UFUNCTION(BlueprintCallable, Category = "UI|GameOver")
	void HideGameOver();

	// UI - GameClear
	UFUNCTION(BlueprintCallable, Category = "UI|GameClear")
	void ShowGameClear();
	UFUNCTION(BlueprintCallable, Category = "UI|GameClear")
	void HideGameClear();

	// UI - GameHUD
	UFUNCTION(BlueprintCallable, Category = "UI|GameHUD")
	void ShowGameHUD();
	UFUNCTION(BlueprintCallable, Category = "UI|GameHUD")
	void HideGameHUD();

	// GameHUD Updates
	UFUNCTION(BlueprintCallable, Category = "UI|GameHUD|Updates")
	void UpdateGameHUDStage(FName StageName, int32 StageNumber);  // GameHUD의 스테이지 UI 업데이트
	UFUNCTION(BlueprintCallable, Category = "UI|GameHUD|Updates")
	void UpdateGameHUDWave(int32 WaveNumber, int32 MaxWaveNumber);  // GameHUD의 웨이브 UI 업데이트
	UFUNCTION(BlueprintCallable, Category = "UI|GameHUD|Updates")
	void UpdateGameHUDTime(float RemainingTime, float TotalTime);  // GameHUD의 시간 UI 업데이트
	UFUNCTION(BlueprintCallable, Category = "UI|GameHUD|Updates")
	void UpdateGameHUDScore(int32 Score);  // GameHUD의 점수 UI 업데이트
	UFUNCTION(BlueprintCallable, Category = "UI|GameHUD|Updates")
	void UpdateGameHUDCoin(int32 CollectedCoinCount, int32 TotalCoinCount);  // GameHUD의 코인 UI 업데이트
	UFUNCTION(BlueprintCallable, Category = "UI|GameHUD|Updates")
	void UpdateGameHUDHealth(int32 Health, int32 MaxHealth);  // GameHUD의 체력 UI 업데이트
	UFUNCTION(BlueprintCallable, Category = "UI|GameHUD|Updates")
	void UpdateGameHUDEffect();  // GameHUD의 이펙트 UI 업데이트
};
