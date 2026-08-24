#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameState.h"

#include "SpartaGameState.generated.h"

UCLASS()
class SPARTACH3ASSIGNMENT3_API ASpartaGameState : public AGameState
{
	GENERATED_BODY()

  public:
	ASpartaGameState();

  protected:
	// Life Cycle Methods
	virtual void BeginPlay() override;
	void StartLevel();
	void EndLevel();

  public:
	// Event Methods
	void OnCoinCollected();
	void OnTimeExpired();
	void OnPlayerDead();

  protected:
	// Handler Methods
	void HandleGameOver();
	void HandleGameCleared();

  public:
	// Modifier Methods
	UFUNCTION(BlueprintCallable, Category = "Actions|Score")
	void AddScore(int32 Amount);

  protected:
	// Game Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData|Score")
	int32 Score;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData|Coin")
	int32 SpawnedCoinCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData|Coin")
	int32 CollectedCointCount;

	UPROPERTY()
	FTimerHandle LevelTimerHandle;
};
