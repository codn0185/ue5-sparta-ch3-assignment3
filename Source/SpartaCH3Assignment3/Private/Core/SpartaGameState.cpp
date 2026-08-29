#include "Core/SpartaGameState.h"

#include "Core/SpartaGameInstance.h"
#include "Data/StageDataRow.h"
#include "Data/WaveDataRow.h"
#include "Items/CoinItem.h"
#include "Kismet/GameplayStatics.h"
#include "World/ItemSpawnVolume.h"

ASpartaGameState::ASpartaGameState()
{
	PrimaryActorTick.bCanEverTick = false;

	// GameData
	StageScore = 0;

	// Wave
	CurrentWaveIndex = 0;

	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
}

void ASpartaGameState::BeginPlay()
{
	Super::BeginPlay();

	// 게임 인스턴스 검증
	if (!GetGameInstance<USpartaGameInstance>())
	{
		UE_LOG(LogTemp, Error, TEXT("ASpartaGameState::BeginPlay() - SpartaGameInstance 로드 실패"));
		return;
	}

	// 게임 시작
	InitializeStage();
}

void ASpartaGameState::InitializeStage()
{
	UE_LOG(LogTemp, Warning, TEXT("ASpartaGameState::InitializeStage()"));

	// Stage 정보 초기화
	StageData = *GetGameInstance<USpartaGameInstance>()->GetCurrentStageData();
	StageScore = 0;

	// Stage 정보 초기화
	CurrentWaveIndex = 0;

	// 웨이브 시작
	StartWave();
}

void ASpartaGameState::ClearStage()
{
	UE_LOG(LogTemp, Warning, TEXT("ASpartaGameState::ClearStage()"));

	// 타이머 정리
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);

	// GameInstance의 OnStageClear() 호출
	GetGameInstance<USpartaGameInstance>()->OnStageClear();
}

void ASpartaGameState::StartWave()
{
	UE_LOG(LogTemp, Warning, TEXT("ASpartaGameState::StartWave() - Wave %d"), CurrentWaveIndex + 1);

	// Wave 정보 초기화
	const UDataTable *WaveDataTable = StageData.WaveDataTable;
	const TArray<FName> RowNames = WaveDataTable->GetRowNames();
	if (RowNames.IsValidIndex(CurrentWaveIndex))
	{
		WaveData = *WaveDataTable->FindRow<FWaveDataRow>(RowNames[CurrentWaveIndex], TEXT("ASpartaGameState::StartWave"));
	}

	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	// 액터 소환
	StartItemSpawn();
	StartSpikeTrapSpawn();
	StartFallingObjectSpawn();

	// 타이머 설정 - 제한 시간 적용
	const float WaveTime = WaveData.WaveTime;

	GetWorldTimerManager().SetTimer(
		WaveTimerHandle,
		this,
		&ASpartaGameState::OnTimeExpired,
		WaveTime,
		false);
}

void ASpartaGameState::EndWave()
{
	UE_LOG(LogTemp, Warning, TEXT("ASpartaGameState::EndWave()"));

	// 이전 웨이브 액터 제거
	for (AActor *Actor : WaveActors)
	{
		if (IsValid(Actor))
		{
			Actor->Destroy();
		}
	}
	WaveActors.Empty();

	// 다음 웨이브 설정
	CurrentWaveIndex++;

	// 마지막 웨이브인 경우
	if (CurrentWaveIndex >= StageData.WaveDataTable->GetRowMap().Num())
	{
		ClearStage();
		return;
	}

	// 다음 웨이브 진행
	StartWave();
}

void ASpartaGameState::OnTimeExpired()
{
	UE_LOG(LogTemp, Warning, TEXT("Time Expired"));

	EndWave();
}

void ASpartaGameState::NotifyCoinCollected(int32 Score)
{
	CollectedCoinCount++;
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
	if (CollectedCoinCount >= SpawnedCoinCount)
	{
		EndWave();
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

void ASpartaGameState::StartItemSpawn()
{
	// Wave 데이터 확인
	const int32 SpawnItemCount = WaveData.ItemCount;
	UDataTable *ItemDataTable = WaveData.ItemSpawnTable;

	// SpawnVolume 찾기
	TArray<AActor *> SpawnVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawnVolume::StaticClass(), SpawnVolumes);

	if (SpawnVolumes.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("AMyGameState::StartItemSpawn() - No SpawnVolume In Current Level"));
		return;
	}

	AItemSpawnVolume *ItemSpawnVolume = Cast<AItemSpawnVolume>(SpawnVolumes[0]);
	if (!ItemSpawnVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("AMyGameState::StartItemSpawn() - No SpawnVolume In Current Level"));
		return;
	}

	// 아이템 소환
	ItemSpawnVolume->SetItemSpawnTable(ItemDataTable);
	for (int i = 0; i < SpawnItemCount; i++)
	{
		AActor *SpawnedActor = ItemSpawnVolume->SpawnActor();
		if (!SpawnedActor)
		{
			continue;
		}
		if (SpawnedActor->IsA(ACoinItem::StaticClass()))
		{
			SpawnedCoinCount++;
		}

		WaveActors.Add(SpawnedActor);
	}

	// TODO: 코인 아이템 최소 보장 (1개 이상 필수)
	// 임시 코드
	if (SpawnedCoinCount <= 0)
	{
		UE_LOG(LogTemp, Error, TEXT("AMyGameState::StartItemSpawn() - SpawnedCoinCount is 0"));

		EndWave();
		return;
	}
}

void ASpartaGameState::StartSpikeTrapSpawn()
{
}

void ASpartaGameState::StartFallingObjectSpawn()
{
}
