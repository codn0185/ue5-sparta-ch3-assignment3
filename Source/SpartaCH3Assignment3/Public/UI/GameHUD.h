#pragma once

#include "CoreMinimal.h"

#include "Blueprint/UserWidget.h"

#include "GameHUD.generated.h"

class UStageWidget;
class UWaveWidget;
class UTimeWidget;
class UScoreWidget;
class UCoinWidget;
class UHealthWidget;

UCLASS()
class SPARTACH3ASSIGNMENT3_API UGameHUD : public UUserWidget
{
	GENERATED_BODY()

  protected:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UStageWidget> StageWidget;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UWaveWidget> WaveWidget;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTimeWidget> TimeWidget;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UScoreWidget> ScoreWidget;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCoinWidget> CoinWidget;
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UHealthWidget> HealthWidget;

  public:
	void SetStage(FName StageName, int32 StageNumber);
	void SetWave(int32 WaveNumber, int32 MaxWaveNumber);
	void SetTime(float RemainingTime, float TotalTime);
	void SetScore(int32 Score);
	void SetCoin(int32 CollectedCoinCount, int32 TotalCoinCount);
	void SetHealth(int32 Health, int32 MaxHealth);
};
