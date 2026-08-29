#pragma once

#include "CoreMinimal.h"

#include "World/SpawnVolumeBase.h"

#include "SpikeTrapSpawnVolume.generated.h"

UCLASS()
class SPARTACH3ASSIGNMENT3_API ASpikeTrapSpawnVolume : public ASpawnVolumeBase
{
	GENERATED_BODY()

  protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Debug")
	bool bEnableDebug;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Config")
	TSubclassOf<AActor> SpikeTrapClass;

  private:
	static const FIntPoint INVALID_GRID;  // 유효하지 않은 격자 좌표

	TArray<TArray<bool>> SpawnGrid;  // 격자 별 배치 여부
	FVector2D GridSize2D;            // 격자 영역 크기 (간격)
	FVector2D GridOrigin2D;          // (0, 0) 격자 영역의 중심 위치

	int32 TotalGridCount;     // 전체 격자 개수
	int32 OccupiedGridCount;  // 점유된 격자 개수

  public:
	ASpikeTrapSpawnVolume();

  protected:
	virtual void BeginPlay() override;

  public:
	virtual AActor* SpawnActor() override;

  private:
	void InitializeGrid();                                                   // 격자 정보 초기화
	FIntPoint GetRandomSpawnableGrid() const;                                // 소환 가능한 무작위 격자 좌표 반환
	FVector2D GetWorldLocationFromGrid2D(const FIntPoint& GridPoint) const;  // 격자 좌표에 해당하는 월드 좌표 반환
	bool HasAvailableGrid() const;                                           // 배치 가능한 격자 존재 여부 확인

	void DrawDebugGrid() const;  // 디버깅 - 격자 그리기
};
