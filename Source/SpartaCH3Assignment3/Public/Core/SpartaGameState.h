#pragma once

#include "CoreMinimal.h"

#include "Data/StageDataRow.h"
#include "Data/WaveDataRow.h"
#include "GameFramework/GameState.h"

#include "SpartaGameState.generated.h"

UCLASS()
class SPARTACH3ASSIGNMENT3_API ASpartaGameState : public AGameState
{
	GENERATED_BODY()

  protected:
	// Stage
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stage|Data")
	FStageDataRow StageData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Stage|State")
	int32 StageScore;

	// Wave
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave|Data")
	FWaveDataRow WaveData;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave|State")
	int32 CurrentWaveIndex;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave|State")
	int32 SpawnedCoinCount;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Wave|State")
	int32 CollectedCoinCount;

	UPROPERTY()
	FTimerHandle WaveTimerHandle;

  private:
	TArray<TObjectPtr<AActor>> WaveActors;  // 현재 웨이브 동안 관리하는 액터

  public:
	ASpartaGameState();

  protected:
	virtual void BeginPlay() override;

	// Stage
	void InitializeStage();
	void ClearStage();

	// Wave
	void StartWave();
	void EndWave();

	// Events
	void OnTimeExpired();

  public:
	// Notifies
	void NotifyCoinCollected(int32 Score);
	void NotifyPlayerDead();

  private:
	UFUNCTION(BlueprintCallable)
	void StartItemSpawn();
	UFUNCTION(BlueprintCallable)
	void StartSpikeTrapSpawn();
	UFUNCTION(BlueprintCallable)
	void StartFallingObjectSpawn();
};
