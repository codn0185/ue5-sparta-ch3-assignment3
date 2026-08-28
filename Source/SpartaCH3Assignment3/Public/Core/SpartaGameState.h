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
	virtual void BeginPlay() override;

	// Life Cycles
	void InitializeLevel();
	void ClearStage();

	// Events
	void OnTimeExpired();

  public:
	// Notifies
	void NotifyCoinCollected(int32 Score);
	void NotifyPlayerDead();

  protected:
	// Game Data
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData|Score")
	int32 StageScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData|Coin")
	int32 SpawnedCoinCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "GameData|Coin")
	int32 CollectedCointCount;

	UPROPERTY()
	FTimerHandle LevelTimerHandle;

  private:
	UFUNCTION(BlueprintCallable)
	void StartItemSpawn();
	UFUNCTION(BlueprintCallable)
	void StartSpikeTrapSpawn();
	UFUNCTION(BlueprintCallable)
	void StartFallingObjectSpawn();
};
