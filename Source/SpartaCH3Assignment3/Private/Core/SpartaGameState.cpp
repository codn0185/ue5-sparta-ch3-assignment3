#include "Core/SpartaGameState.h"

#include "Core/SpartaGameInstance.h"
#include "Data/StageDataRow.h"
#include "Items/CoinItem.h"
#include "Kismet/GameplayStatics.h"
#include "World/ItemSpawnVolume.h"

ASpartaGameState::ASpartaGameState()
{
	PrimaryActorTick.bCanEverTick = false;

	// GameData
	StageScore = 0;
	SpawnedCoinCount = 0;
	CollectedCointCount = 0;
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();

	InitializeLevel();
}

void ASpartaGameState::InitializeLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("ASpartaGameState::InitializeLevel()"));

	// GameInstance에서 현재 스테이지의 제한 시간, 소환 개수, 아이템 데이터 테이블 받아오기
	float StageDuration = 0.f;
	int32 SpawnItemCount = 0;
	UDataTable *ItemDataTable = nullptr;
	if (UGameInstance *GameInstance = GetGameInstance())
	{
		if (USpartaGameInstance *SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance))
		{
			const FStageDataRow *StageDate = SpartaGameInstance->GetCurrentStageData();
			StageDuration = StageDate->TimeLimit;
			SpawnItemCount = StageDate->ItemCount;
			ItemDataTable = StageDate->ItemSpawnTable;
		}
	}

	// GameData 초기화
	StageScore = 0;
	SpawnedCoinCount = 0;
	CollectedCointCount = 0;

	// SpawnVolume 찾기
	TArray<AActor *> SpawnVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawnVolume::StaticClass(), SpawnVolumes);

	if (SpawnVolumes.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("AMyGameState::BeginPlay - No SpawnVolume In Current Level"));
		return;
	}

	AItemSpawnVolume *ItemSpawnVolume = Cast<AItemSpawnVolume>(SpawnVolumes[0]);
	if (!ItemSpawnVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("AMyGameState::BeginPlay - No SpawnVolume In Current Level"));
		return;
	}

	// 아이템 소환
	ItemSpawnVolume->SetItemSpawnTable(ItemDataTable);
	for (int i = 0; i < SpawnItemCount; i++)
	{
		AActor *SpawnedActor = ItemSpawnVolume->SpawnActor();
		if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
		{
			SpawnedCoinCount++;
		}
	}

	// TODO: 코인 아이템 최소 보장 (1개 이상 필수)
	// 임시 코드
	if (SpawnedCoinCount <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("AMyGameState::BeginPlay - SpawnedCoinCount is 0"));
		return;
	}

	// 타이머 설정 - 제한 시간 적용
	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&ASpartaGameState::OnTimeExpired,
		StageDuration,
		false);
}

void ASpartaGameState::ClearStage()
{
	UE_LOG(LogTemp, Warning, TEXT("ASpartaGameState::ClearStage()"));

	// 타이머 정리
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	// GameInstance의 OnStageClear() 호출 - 다음 스테이지 진행 or 게임 클리어
	if (UGameInstance *GameInstance = GetGameInstance())
	{
		if (USpartaGameInstance *SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance))
		{
			SpartaGameInstance->OnStageClear();
		}
	}
}

void ASpartaGameState::OnTimeExpired()
{
	UE_LOG(LogTemp, Warning, TEXT("Time Expired"));
	ClearStage();
}

void ASpartaGameState::NotifyCoinCollected(int32 Score)
{
	CollectedCointCount++;
	StageScore += Score;

	// GameInstance의 전역 점수에 추가
	if (UGameInstance *GameInstance = GetGameInstance())
	{
		if (USpartaGameInstance *SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance))
		{
			SpartaGameInstance->AddScore(Score);
		}
	}

	// 스테이지 클리어 조건 만족
	if (CollectedCointCount >= SpawnedCoinCount)
	{
		ClearStage();
	}
}

void ASpartaGameState::NotifyPlayerDead()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Dead"));

	// GameInstance의 OnGameOver() 호출
	if (UGameInstance *GameInstance = GetGameInstance())
	{
		if (USpartaGameInstance *SpartaGameInstance = Cast<USpartaGameInstance>(GameInstance))
		{
			SpartaGameInstance->OnGameOver();
		}
	}
}
