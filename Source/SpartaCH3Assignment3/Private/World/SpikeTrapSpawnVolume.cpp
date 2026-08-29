#include "World/SpikeTrapSpawnVolume.h"

#include "DrawDebugHelpers.h"

#include "Components/BoxComponent.h"
#include "Obstacles/SpikeTrap.h"

const FIntPoint ASpikeTrapSpawnVolume::INVALID_GRID(-1, -1);

ASpikeTrapSpawnVolume::ASpikeTrapSpawnVolume()
{
	bEnableDebug = false;
}

void ASpikeTrapSpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	// 격자 초기화
	InitializeGrid();

	// 디버깅
	if (bEnableDebug)
	{
		DrawDebugGrid();
	}
}

AActor* ASpikeTrapSpawnVolume::SpawnActor()
{
	// 소환 가능한 상태인지 확인
	if (!SpikeTrapClass || !HasAvailableGrid())
	{
		return nullptr;
	}

	// 소환할 격자 및 위치 구하기
	const FIntPoint SpawnGridPoint = GetRandomSpawnableGrid();
	const FVector2D SpawnLocation2D = GetWorldLocationFromGrid2D(SpawnGridPoint);
	const FVector SpawnLocation = FVector(
		SpawnLocation2D.X,
		SpawnLocation2D.Y,
		GetActorLocation().Z - SpawnBox->GetScaledBoxExtent().Z);

	// 액터 소환
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(
		SpikeTrapClass,
		SpawnLocation,
		FRotator::ZeroRotator);

	// 소환된 격자 점유 처리
	SpawnGrid[SpawnGridPoint.Y][SpawnGridPoint.X] = true;
	OccupiedGridCount++;

	return SpawnedActor;
}

void ASpikeTrapSpawnVolume::InitializeGrid()
{
	// SpikeTrapClass가 지정되지 않은 경우
	if (!SpikeTrapClass)
	{
		return;
	}

	// SpikeTrap 크기를 기준으로 격자 크기 설정
	const ASpikeTrap* SpikeTrapCDO = SpikeTrapClass->GetDefaultObject<ASpikeTrap>();
	const FVector SpikeTrapSize = SpikeTrapCDO->GetSize();

	// GridSize2D 초기화
	GridSize2D = FVector2D(
		SpikeTrapSize.X,
		SpikeTrapSize.Y);

	// SpawnBox의 중심 및 크기 확인
	const FVector BoxCenter = SpawnBox->GetComponentLocation();
	const FVector BoxExtent = SpawnBox->GetScaledBoxExtent();

	// SpikeTrap 전체가 SpawnBox 내부에 들어갈 수 있는 영역
	const FVector2D SpawnableExtent(
		BoxExtent.X - SpikeTrapSize.X * 0.5f,
		BoxExtent.Y - SpikeTrapSize.Y * 0.5f);

	// SpikeTrap을 배치할 수 없는 크기인 경우
	if (SpawnableExtent.X < 0.f || SpawnableExtent.Y < 0.f)
	{
		return;
	}

	// SpawnBox 내부에 배치할 수 있는 격자 개수
	const int32 GridCountX = FMath::FloorToInt((SpawnableExtent.X * 2.f) / GridSize2D.X) + 1;
	const int32 GridCountY = FMath::FloorToInt((SpawnableExtent.Y * 2.f) / GridSize2D.Y) + 1;

	// 유효한 격자가 없는 경우
	if (GridCountX <= 0 || GridCountY <= 0)
	{
		return;
	}

	// SpawnGrid 초기화
	SpawnGrid.SetNum(GridCountY);
	for (TArray<bool>& Row : SpawnGrid)
	{
		Row.Init(false, GridCountX);
	}

	// TotalGridCount 및 OccupiedGridCount 초기화
	TotalGridCount = GridCountX * GridCountY;
	OccupiedGridCount = 0;

	// GridOrigin2D 초기화
	GridOrigin2D = FVector2D(
		BoxCenter.X - BoxExtent.X + GridSize2D.X * 0.5f,
		BoxCenter.Y - BoxExtent.Y + GridSize2D.Y * 0.5f);
}

FIntPoint ASpikeTrapSpawnVolume::GetRandomSpawnableGrid() const
{
	// 소환 가능한 격자 있는지 확인
	if (!HasAvailableGrid())
	{
		return INVALID_GRID;
	}

	// 비어 있는 격자 좌표 확인
	TArray<FIntPoint> AvailableGrids;
	for (int32 Y = 0; Y < SpawnGrid.Num(); Y++)
	{
		for (int32 X = 0; X < SpawnGrid[Y].Num(); X++)
		{
			if (!SpawnGrid[Y][X])
			{
				AvailableGrids.Add(FIntPoint(X, Y));
			}
		}
	}

	// 비어 있는 격자 중 무작위 선택
	int32 Index = FMath::RandRange(0, AvailableGrids.Num() - 1);
	return AvailableGrids[Index];
}

FVector2D ASpikeTrapSpawnVolume::GetWorldLocationFromGrid2D(const FIntPoint& GridPoint) const
{
	return GridOrigin2D + FVector2D(
							  GridPoint.X * GridSize2D.X,
							  GridPoint.Y * GridSize2D.Y);
}

bool ASpikeTrapSpawnVolume::HasAvailableGrid() const
{
	return OccupiedGridCount < TotalGridCount;
}

void ASpikeTrapSpawnVolume::DrawDebugGrid() const
{
	if (!GetWorld())
	{
		return;
	}

	const FVector Extent(  // 디버그 박스 크기
		GridSize2D.X * 0.5f,
		GridSize2D.Y * 0.5f,
		SpawnBox ? SpawnBox->GetScaledBoxExtent().Z : 10.f);

	for (int32 Y = 0; Y < SpawnGrid.Num(); Y++)
	{
		for (int32 X = 0; X < SpawnGrid[Y].Num(); X++)
		{
			const FVector2D WorldLocation2D = GetWorldLocationFromGrid2D(FIntPoint(X, Y));

			const FVector Center(  // 디버그 박스 중심
				WorldLocation2D.X,
				WorldLocation2D.Y,
				GetActorLocation().Z);

			DrawDebugBox(
				GetWorld(),
				Center,
				Extent,
				FColor::Green,
				true,
				-1.f,
				0,
				2.f);
		}
	}
}
