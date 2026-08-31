#pragma once

#include "CoreMinimal.h"

#include "Engine/GameInstance.h"

#include "SpartaGameInstance.generated.h"

struct FStageDataRow;

UENUM(BlueprintType)
enum class EGameState
{
	MainMenu,
	Playing,
	GameOver,
	GameClear,
};

UCLASS()
class SPARTACH3ASSIGNMENT3_API USpartaGameInstance : public UGameInstance
{
	GENERATED_BODY()

  protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game|State")
	EGameState CurrentGameState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game|Data")
	TObjectPtr<UDataTable> StageDataTable;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game|Data")
	int32 CurrentStageIndex;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game|Data")
	int32 TotalScore;

  public:
	USpartaGameInstance();

	UFUNCTION(BlueprintCallable, Category = "Game|Flows")
	void StartGame();
	UFUNCTION(BlueprintCallable, Category = "Game|Flows")
	void StartStage();

	UFUNCTION(BlueprintCallable, Category = "Game|Flows")
	void OnStageClear();
	UFUNCTION(BlueprintCallable, Category = "Game|Flows")
	void OnGameOver();
	UFUNCTION(BlueprintCallable, Category = "Game|Flows")
	void OnGameClear();

	void AddScore(int32 Score);

	const FStageDataRow* GetCurrentStageData() const;
	int32 GetCurrentStageIndex() const;
	int32 GetMaxStageIndex() const;
	int32 GetTotalScore() const;
};
