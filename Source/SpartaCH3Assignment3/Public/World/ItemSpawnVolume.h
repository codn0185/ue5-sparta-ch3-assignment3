#pragma once

#include "CoreMinimal.h"

#include "World/SpawnVolumeBase.h"

#include "ItemSpawnVolume.generated.h"

UCLASS()
class SPARTACH3ASSIGNMENT3_API AItemSpawnVolume : public ASpawnVolumeBase
{
	GENERATED_BODY()

  protected:
	UPROPERTY()
	TObjectPtr<UDataTable> ItemSpawnTable;

  public:
	virtual AActor* SpawnActor() override;

	UFUNCTION(BlueprintCallable)
	void SetItemSpawnTable(UDataTable* InItemSpawnTable);

  private:
	UFUNCTION(BlueprintPure)
	TSubclassOf<AActor> GetRandomItem() const;
};
