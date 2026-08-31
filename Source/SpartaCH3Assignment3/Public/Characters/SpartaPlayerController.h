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

	// UI - HUD
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UI|GameHUD")
	TSubclassOf<UUserWidget> GameHUDWidgetClass;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "UI|GameHUD")
	UUserWidget* GameHUDWidget;

  protected:
	virtual void BeginPlay() override;

  public:
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

	// UI - HUD
	UFUNCTION(BlueprintCallable, Category = "UI|GameHUD")
	void ShowGameHUD();
	UFUNCTION(BlueprintCallable, Category = "UI|GameHUD")
	void HideGameHUD();
};
