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

	// 게임 인스턴스 검증
	if (!GetGameInstance<USpartaGameInstance>())
	{
		UE_LOG(LogTemp, Error, TEXT("ASpartaGameState::BeginPlay() - SpartaGameInstance 로드 실패"));
		return;
	}

	// 게임 시작
	InitializeLevel();
}

void ASpartaGameState::InitializeLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("ASpartaGameState::InitializeLevel()"));

	// GameData 초기화
	StageScore = 0;
	SpawnedCoinCount = 0;
	CollectedCointCount = 0;

	// 액터 소환
	StartItemSpawn();
	StartSpikeTrapSpawn();
	StartFallingObjectSpawn();

	// 타이머 설정 - 제한 시간 적용
	const FStageDataRow *StageDate = GetGameInstance<USpartaGameInstance>()->GetCurrentStageData();
	const float StageDuration = StageDate->TimeLimit;

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

	// GameInstance의 OnStageClear() 호출
	GetGameInstance<USpartaGameInstance>()->OnStageClear();
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

void ASpartaGameState::StartItemSpawn()
{
	// GameInstance에서 필요한 정보 로드
	const FStageDataRow *StageDate = GetGameInstance<USpartaGameInstance>()->GetCurrentStageData();
	const float StageDuration = StageDate->TimeLimit;
	const int32 SpawnItemCount = StageDate->ItemCount;
	UDataTable *ItemDataTable = StageDate->ItemSpawnTable;

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
}

void ASpartaGameState::StartSpikeTrapSpawn()
{
}

void ASpartaGameState::StartFallingObjectSpawn()
{
}
