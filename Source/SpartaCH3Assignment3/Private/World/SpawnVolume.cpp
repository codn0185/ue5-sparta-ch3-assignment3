#include "World/SpawnVolume.h"

#include "Components/BoxComponent.h"
#include "Data/ItemSpawnRow.h"

ASpawnVolume::ASpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	SpawnBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawning Box"));
	SetRootComponent(SpawnBox);

	SpawnMargin = FVector::ZeroVector;
}

AActor* ASpawnVolume::SpawnRandomItem(const UDataTable* ItemSpawnDataTable)
{
	if (TSubclassOf<AActor> Item = GetRandomItem(ItemSpawnDataTable))
	{
		if (UClass* ItemClass = Item.Get())
		{
			return GetWorld()->SpawnActor<AActor>(
				ItemClass,
				GetRandomPoint(),
				FRotator::ZeroRotator);
		}
	}

	return nullptr;
}

TSubclassOf<AActor> ASpawnVolume::GetRandomItem(const UDataTable* ItemSpawnDataTable) const
{
	// 데이터테이블 로드
	if (!ItemSpawnDataTable)
	{
		return nullptr;
	}

	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("ASpawnVolume::GetRandomItem - Failed to get all item rows from DataTable"));
	ItemSpawnDataTable->GetAllRows(ContextString, AllRows);

	if (AllRows.IsEmpty())
	{
		return nullptr;
	}

	// 확률 계산
	float TotalChance = 0.0f;
	for (const FItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			TotalChance += Row->SpawnChance;
		}
	}

	const float RandomValue = FMath::FRandRange(0.f, TotalChance);
	float AccumulateChance = 0.f;
	for (FItemSpawnRow* Row : AllRows)
	{
		if (Row)
		{
			AccumulateChance += Row->SpawnChance;
			if (RandomValue <= AccumulateChance)
			{
				return Row->ItemClass;
			}
		}
	}

	return nullptr;
}

FVector ASpawnVolume::GetRandomPoint() const
{
	if (!SpawnBox)
	{
		return FVector::ZeroVector;
	}

	// 소환 위치 및 범위 확인
	FVector BoxOrigin = SpawnBox->GetComponentLocation();
	FVector BoxExtent = SpawnBox->GetScaledBoxExtent();

	// 여백을 적용한 유효 범위 (음수 방지)
	FVector SafeExtent = (BoxExtent - SpawnMargin).ComponentMax(FVector::ZeroVector);

	// 무작위 위치 반환
	return BoxOrigin + FVector(
						   FMath::FRandRange(-SafeExtent.X, SafeExtent.X),
						   FMath::FRandRange(-SafeExtent.Y, SafeExtent.Y),
						   FMath::FRandRange(-SafeExtent.Z, SafeExtent.Z));
}
