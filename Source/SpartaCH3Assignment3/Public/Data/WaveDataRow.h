#pragma once

#include "CoreMinimal.h"

#include "WaveDataRow.generated.h"

USTRUCT(BlueprintType)
struct FWaveDataRow : public FTableRowBase
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 WaveNumber;  // 웨이브 번호
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float WaveTime;  // 웨이브 시간 (초)

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ItemCount;  // 아이템 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataTable> ItemSpawnTable;  // 아이템 소환 테이블

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SpikeTrapCount;  // 가시 발판 개수

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 FallingObstacleCount;  // 낙하 장애물 동시 소환 개수
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FallingObstacleSpawnInterval;  // 낙하 장애물 소환 간격 (초)
};
