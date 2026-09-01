#include "UI/GameHUD.h"

#include "UI/CoinWidget.h"
#include "UI/HealthWidget.h"
#include "UI/ScoreWidget.h"
#include "UI/StageWidget.h"
#include "UI/TimeWidget.h"
#include "UI/WaveWidget.h"

void UGameHUD::SetStage(FName StageName, int32 StageNumber)
{
	StageWidget->SetStage(StageName, StageNumber);
}

void UGameHUD::SetWave(int32 WaveNumber, int32 MaxWaveNumber)
{
	WaveWidget->SetWave(WaveNumber, MaxWaveNumber);
}

void UGameHUD::SetTime(float RemainingTime, float TotalTime)
{
	TimeWidget->SetTime(RemainingTime, TotalTime);
}

void UGameHUD::SetScore(int32 Score)
{
	ScoreWidget->SetScore(Score);
}

void UGameHUD::SetCoin(int32 CollectedCoinCount, int32 TotalCoinCount)
{
	CoinWidget->SetCoin(CollectedCoinCount, TotalCoinCount);
}

void UGameHUD::SetHealth(int32 Health, int32 MaxHealth)
{
	HealthWidget->SetHealth(Health, MaxHealth);
}
