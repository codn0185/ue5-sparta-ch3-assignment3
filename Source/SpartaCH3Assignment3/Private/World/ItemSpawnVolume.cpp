#include "World/ItemSpawnVolume.h"

#include "Data/ItemSpawnRow.h"

AActor* AItemSpawnVolume::SpawnActor()
{
	if (TSubclassOf<AActor> ItemActor = GetRandomItem())
	{
		if (UClass* ItemActorClass = ItemActor.Get())
		{
			return GetWorld()->SpawnActor<AActor>(
				ItemActorClass,
				GetRandomSpawnLocation(),
				FRotator::ZeroRotator);
		}
	}

	return nullptr;
}

void AItemSpawnVolume::SetItemSpawnTable(UDataTable* InItemSpawnTable)
{
	ItemSpawnTable = InItemSpawnTable;
}

TSubclassOf<AActor> AItemSpawnVolume::GetRandomItem() const
{
	// 데이터테이블 확인
	if (!ItemSpawnTable)
	{
		return nullptr;
	}

	TArray<FItemSpawnRow*> AllRows;
	static const FString ContextString(TEXT("AItemSpawnVolume::GetRandomItem()"));
	ItemSpawnTable->GetAllRows(ContextString, AllRows);

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
