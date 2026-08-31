#include "Core/SpartaGameInstance.h"

#include "Data/StageDataRow.h"
#include "Kismet/GameplayStatics.h"

USpartaGameInstance::USpartaGameInstance()
	: StageDataTable(nullptr),
	  CurrentStageIndex(0),
	  TotalScore(0)
{
}

void USpartaGameInstance::StartGame()
{
	UE_LOG(LogTemp, Warning, TEXT("USpartaGameInstance::StartGame()"));

	CurrentStageIndex = 0;
	TotalScore = 0;

	StartStage();
}

void USpartaGameInstance::StartStage()
{
	UE_LOG(LogTemp, Warning, TEXT("USpartaGameInstance::StartStage()"));

	// 현재 스테이지 맵 로드
	const FStageDataRow* StageData = GetCurrentStageData();
	if (!StageData || StageData->Level.IsNull())
	{
		return;
	}

	UGameplayStatics::OpenLevelBySoftObjectPtr(this, StageData->Level);
}

void USpartaGameInstance::OnStageClear()
{
	UE_LOG(LogTemp, Warning, TEXT("USpartaGameInstance::OnStageClear()"));

	// 다음 스테이지
	CurrentStageIndex++;

	// 마지막 스테이지 - 게임 클리어
	if (!GetCurrentStageData())
	{
		OnGameClear();
		return;
	}

	// 다음 스테이지 진행
	StartStage();
}

void USpartaGameInstance::OnGameOver()
{
	// 게임 오버
	UE_LOG(LogTemp, Warning, TEXT("USpartaGameInstance::OnGameOver()"));
}

void USpartaGameInstance::OnGameClear()
{
	// 게임 클리어
	UE_LOG(LogTemp, Warning, TEXT("USpartaGameInstance::OnGameClear()"));
}

void USpartaGameInstance::AddScore(int32 Score)
{
	TotalScore += Score;
}

const FStageDataRow* USpartaGameInstance::GetCurrentStageData() const
{
	if (!StageDataTable)
	{
		return nullptr;
	}

	const TArray<FName> RowNames = StageDataTable->GetRowNames();

	if (RowNames.IsValidIndex(CurrentStageIndex))
	{
		return StageDataTable->FindRow<FStageDataRow>(RowNames[CurrentStageIndex], TEXT("USpartaGameInstance::GetCurrentStageData"));
	}

	return nullptr;
}

int32 USpartaGameInstance::GetCurrentStageIndex() const
{
	return CurrentStageIndex;
}

int32 USpartaGameInstance::GetMaxStageIndex() const
{
	return StageDataTable->GetRowNames().Num();
}

int32 USpartaGameInstance::GetTotalScore() const
{
	return TotalScore;
}
