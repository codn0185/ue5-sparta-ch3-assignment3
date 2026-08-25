#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "SpawnVolume.generated.h"

class UBoxComponent;

UCLASS()
class SPARTACH3ASSIGNMENT3_API ASpawnVolume : public AActor
{
	GENERATED_BODY()

  public:
	ASpawnVolume();

  protected:
	// Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* SpawnBox;

	// Properties
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Properties", meta = (ClampMin = "0.0", UIMin = "0.0"))
	FVector SpawnMargin;  // 소환 마진

  public:
	UFUNCTION(BlueprintCallable)
	AActor* SpawnRandomItem(const UDataTable* ItemSpawnDataTable);  // 무작위 아이템 소환

  protected:
	UFUNCTION(BlueprintPure)
	TSubclassOf<AActor> GetRandomItem(const UDataTable* ItemSpawnDataTable) const;  // 무작위 아이템 반환
	UFUNCTION(BlueprintPure)
	FVector GetRandomPoint() const;  // 무작위 위치 반환
};
