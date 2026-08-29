#pragma once

#include "CoreMinimal.h"

#include "StageDataRow.generated.h"

USTRUCT(BlueprintType)
struct FStageDataRow : public FTableRowBase
{
	GENERATED_BODY()

  public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName StageName;  // 스테이지 이름
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UWorld> Level;  // 스테이지 맵
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UDataTable> WaveDataTable;  // 웨이브 테이블
};
