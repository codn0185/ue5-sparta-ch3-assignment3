#include "Core/SpartaGameState.h"

#include "Characters/SpartaPlayerController.h"
#include "Core/SpartaGameInstance.h"
#include "Data/StageDataRow.h"
#include "Data/WaveDataRow.h"
#include "Items/CoinItem.h"
#include "Kismet/GameplayStatics.h"
#include "World/FallingObjectSpawnVolume.h"
#include "World/ItemSpawnVolume.h"
#include "World/SpikeTrapSpawnVolume.h"

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

	// 모든 SpawnVolume 찾기
	FindSpawnVolumes();

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

	// GameHUD 업데이트
	if (ASpartaPlayerController *PlayerController = GetWorld()->GetFirstPlayerController<ASpartaPlayerController>())
	{
		// 스테이지
		if (USpartaGameInstance *GameInstance = GetGameInstance<USpartaGameInstance>())
		{
			const FStageDataRow *CurrentStageData = GameInstance->GetCurrentStageData();
			const int32 CurrentStageIndex = GameInstance->GetCurrentStageIndex();
			PlayerController->UpdateGameHUDStage(CurrentStageData->StageName, CurrentStageIndex + 1);
		}
	}

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

	// GameHUD 업데이트
	if (ASpartaPlayerController *PlayerController = GetWorld()->GetFirstPlayerController<ASpartaPlayerController>())
	{
		// 웨이브
		PlayerController->UpdateGameHUDWave(CurrentWaveIndex + 1, StageData.WaveDataTable->GetRowMap().Num());

		// 시간
		TWeakObjectPtr<ASpartaGameState> WeakThis(this);
		TWeakObjectPtr<ASpartaPlayerController> WeakPlayerController(PlayerController);

		GetWorldTimerManager().SetTimer(
			UpdateGameHUDTimeTimerHandle,
			[WeakThis, WeakPlayerController]()
			{
				if (WeakThis.IsValid() && WeakPlayerController.IsValid())
				{
					const float RemainingTime = WeakThis->GetWorldTimerManager().GetTimerRemaining(WeakThis->WaveTimerHandle);
					const float TotalTime = WeakThis->WaveData.WaveTime;
					WeakPlayerController->UpdateGameHUDTime(RemainingTime, TotalTime);
				}
			},
			0.1f,
			true);
	}
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

	// 이전 웨이브 타이머 초기화
	GetWorldTimerManager().ClearTimer(WaveTimerHandle);
	GetWorldTimerManager().ClearTimer(FallingObjectTimerHandle);
	GetWorldTimerManager().ClearTimer(UpdateGameHUDTimeTimerHandle);

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

	// GameHUD 업데이트
	if (ASpartaPlayerController *PlayerController = GetWorld()->GetFirstPlayerController<ASpartaPlayerController>())
	{
		// 코인
		PlayerController->UpdateGameHUDCoin(CollectedCoinCount, SpawnedCoinCount);
	}

	// GameInstance의 전역 점수에 추가
	if (USpartaGameInstance *GameInstance = GetGameInstance<USpartaGameInstance>())
	{
		GameInstance->AddScore(Score);

		// GameHUD 업데이트
		if (ASpartaPlayerController *PlayerController = GetWorld()->GetFirstPlayerController<ASpartaPlayerController>())
		{
			// 점수
			PlayerController->UpdateGameHUDScore(GameInstance->GetTotalScore());
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
	// ItemSpawnVolume이 할당되지 않은 경우
	if (!ItemSpawnVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("ASpartaGameState::StartItemSpawn() - ItemSpawnVolume is Invalid"));
		return;
	}

	// Wave 데이터 확인
	const int32 ItemSpawnCount = WaveData.ItemCount;
	UDataTable *ItemDataTable = WaveData.ItemSpawnTable;

	// 아이템 소환
	ItemSpawnVolume->SetItemSpawnTable(ItemDataTable);
	for (int32 SpawnIndex = 0; SpawnIndex < ItemSpawnCount; SpawnIndex++)
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

	// GameHUD 업데이트
	if (ASpartaPlayerController *PlayerController = GetWorld()->GetFirstPlayerController<ASpartaPlayerController>())
	{
		// 코인
		PlayerController->UpdateGameHUDCoin(CollectedCoinCount, SpawnedCoinCount);
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
	// SpikeTrapSpawnVolume이 할당되지 않은 경우
	if (!SpikeTrapSpawnVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("ASpartaGameState::StartSpikeTrapSpawn() - SpikeTrapSpawnVolume is Invalid"));
		return;
	}

	// 소환 개수
	const int32 SpikeTrapSpawnCount = WaveData.SpikeTrapCount;

	for (int32 SpawnIndex = 0; SpawnIndex < SpikeTrapSpawnCount; SpawnIndex++)
	{
		AActor *SpawnedActor = SpikeTrapSpawnVolume->SpawnActor();
		if (!SpawnedActor)
		{
			continue;
		}

		WaveActors.Add(SpawnedActor);
	}
}

void ASpartaGameState::StartFallingObjectSpawn()
{
	// FallingObjectSpawnVolume이 할당되지 않은 경우
	if (!FallingObjectSpawnVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("ASpartaGameState::StartFallingObjectSpawn() - FallingObjectSpawnVolume is Invalid"));
		return;
	}

	// 소환 개수
	const int32 FallingObstacleSpawnInterval = WaveData.FallingObstacleSpawnInterval;

	GetWorldTimerManager().SetTimer(
		FallingObjectTimerHandle,
		this,
		&ASpartaGameState::SpawnFallingObjects,
		FallingObstacleSpawnInterval,
		true);
}

void ASpartaGameState::SpawnFallingObjects()
{
	// 소환 개수
	const int32 FallingObstacleSpawnCount = WaveData.FallingObstacleCount;

	// 액터 소환
	for (int32 SpawnIndex = 0; SpawnIndex < FallingObstacleSpawnCount; SpawnIndex++)
	{
		AActor *SpawnedActor = FallingObjectSpawnVolume->SpawnActor();
		if (!SpawnedActor)
		{
			continue;
		}

		WaveActors.Add(SpawnedActor);
	}
}

void ASpartaGameState::FindSpawnVolumes()
{
	TArray<AActor *> SpawnVolumes;

	// ItemSpawnVolume 찾기
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AItemSpawnVolume::StaticClass(), SpawnVolumes);

	if (!SpawnVolumes.IsEmpty())
	{
		ItemSpawnVolume = Cast<AItemSpawnVolume>(SpawnVolumes[0]);
	}

	// SpikeTrapSpawnVolume 찾기
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpikeTrapSpawnVolume::StaticClass(), SpawnVolumes);

	if (!SpawnVolumes.IsEmpty())
	{
		SpikeTrapSpawnVolume = Cast<ASpikeTrapSpawnVolume>(SpawnVolumes[0]);
	}

	// FallingObjectSpawnVolume 찾기
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFallingObjectSpawnVolume::StaticClass(), SpawnVolumes);

	if (!SpawnVolumes.IsEmpty())
	{
		FallingObjectSpawnVolume = Cast<AFallingObjectSpawnVolume>(SpawnVolumes[0]);
	}
}
