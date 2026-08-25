#include "Core/SpartaGameState.h"

#include "Items/CoinItem.h"
#include "Kismet/GameplayStatics.h"
#include "World/SpawnVolume.h"

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
	// TODO: GameInstance에서 현재 스테이지의 제한 시간, 소환 개수, 아이템 데이터 테이블 받아오기
	float Duration = 0.f;
	int32 SpawnItemCount = 0;
	UDataTable *ItemDataTable = nullptr;

	// GameData 초기화
	StageScore = 0;
	SpawnedCoinCount = 0;
	CollectedCointCount = 0;

	// SpawnVolume 찾기
	TArray<AActor *> SpawnVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), SpawnVolumes);

	if (SpawnVolumes.IsEmpty())
	{
		UE_LOG(LogTemp, Error, TEXT("AMyGameState::BeginPlay - No SpawnVolume In Current Level"));
		return;
	}

	ASpawnVolume *SpawnVolume = Cast<ASpawnVolume>(SpawnVolumes[0]);
	if (!SpawnVolume)
	{
		UE_LOG(LogTemp, Error, TEXT("AMyGameState::BeginPlay - No SpawnVolume In Current Level"));
		return;
	}

	// 아이템 소환
	for (int i = 0; i < SpawnItemCount; i++)
	{
		AActor *SpawnedActor = SpawnVolume->SpawnRandomItem(ItemDataTable);
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
		Duration,
		false);
}

void ASpartaGameState::ClearStage()
{
	// 타이머 정리
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	// TODO: GameInstance의 OnStageClear() 호출
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
	// TODO: GameInstance의 전역 점수에 적용

	// 스테이지 클리어 조건 만족
	if (CollectedCointCount >= SpawnedCoinCount)
	{
		ClearStage();
	}
}

void ASpartaGameState::NotifyPlayerDead()
{
	UE_LOG(LogTemp, Warning, TEXT("Player Dead"));
	// TODO: GameInstance의 OnGameOver() 호출
}
