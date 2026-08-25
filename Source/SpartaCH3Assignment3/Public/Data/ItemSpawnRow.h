#pragma once

#include "CoreMinimal.h"

#include "ItemSpawnRow.generated.h"

class ABaseItem;

USTRUCT(BlueprintType)
struct FItemSpawnRow : public FTableRowBase
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;  // 아이템 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;  // 아이템 클래스
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance;  // 소환 확률
};
